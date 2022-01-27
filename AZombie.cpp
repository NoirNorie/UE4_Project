// Fill out your copyright notice in the Description page of Project Settings.


#include "AZombie.h"

// Sets default values
AAZombie::AAZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// AI가 컨트롤할 수 있도록 하는 구문
	AIControllerClass = AZombieController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 좀비 애니메이션과 연결
	static ConstructorHelpers::FClassFinder<UZombieAnim>TZombieAnim(TEXT("/Game/Blueprint/Zombie/ZombieAnimation/BPZombieAnimInst"));
	if (TZombieAnim.Succeeded())
	{
		// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("ZombieAnim")));
		GetMesh()->SetAnimInstanceClass(TZombieAnim.Class);
	}

	// 변수 초기화
	Zombie_HP = 100.0f;
	IsAttacking = false;
	IsDeath = false;

	AttackRange = 200.0f;
	AttackRadius = 50.0f;
}

// Called when the game starts or when spawned
void AAZombie::BeginPlay()
{
	Super::BeginPlay();
	
}
// Called every frame
void AAZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Called to bind functionality to input
void AAZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
void AAZombie::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ZombieAnimInst = Cast<UZombieAnim>(GetMesh()->GetAnimInstance());
}
float AAZombie::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDeath != true)
	{
		float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Damage %f"), Damage));
		Zombie_HP -= Damage;
		if (Zombie_HP <= 0)
		{
			Death();
		}
		return Damage;
	}
	return 0;
}
void AAZombie::Attack()
{
	IsAttacking = true;
	ZombieAnimInst->Attack();
	AttackCheck();
}
void AAZombie::Detect()
{
	IsDetect = true;
	ZombieAnimInst->Detect();
}
void AAZombie::OnAttackEnded()
{
	IsDetect = false;
	OnAttackEnd.Broadcast();
}
void AAZombie::OnDetectEnded()
{
	IsAttacking = false;
	OnDetectEnd.Broadcast();
}
void AAZombie::Death() // 좀비가 죽은 것을 처리하는 함수
{
	GetCharacterMovement()->SetMovementMode(MOVE_None); // 더 이상의 이동을 수행하지 못하도록 한다.
	IsDeath = true;
	ZombieAnimInst->IsDead = true;
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 캡슐 컴포넌트도 제거한다.
	GetController()->UnPossess(); // 좀비와 컨트롤러의 연결을 끊는다.

	FTimerHandle WaitHandle;
	float WaitTime = 10.0f;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			Destroy(); // 10초뒤에 월드 상에서 시체도 제거한다.
		}), WaitTime, false);
}

void AAZombie::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult, GetActorLocation(), GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AttackRadius), Params);
	Params.AddIgnoredActor(this);

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeigh = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(), Center, HalfHeigh, 200.0f, CapsuleRot, DrawColor, false, DebugLifeTime);

	if (bResult)
	{
		if (HitResult.GetActor()->ActorHasTag("Player"))
		{
			UE_LOG(LogTemp, Log, TEXT("Hit Actor Name: %s"), *HitResult.Actor->GetName());
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(50.0f, DamageEvent, GetController(), this); // 플레이어에게 데미지를 가한다.
		}
	}
}
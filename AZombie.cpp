// Fill out your copyright notice in the Description page of Project Settings.


#include "AZombie.h"

// Sets default values
AAZombie::AAZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // 틱을 끈다.
	
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

	ZombieDamage = 30.0f;
	AttackRange = 150.0f;
	AttackRadius = 50.0f;
	Tags.Add("Zombie");
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
	if (ZombieAnimInst)
	{
		ZombieAnimInst->OnAttackHitCheck.AddUObject(this, &AAZombie::AttackCheck); // 공격 판정을 실행
	}
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
	ZombieAnimInst->Attack(); // 노티파이로 공격 함수를 동작시킨다.
	// AttackCheck();
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
	ZombieAnimInst->IsDead = true; // 애니메이션에는 사망 동작이 일어나도록 설정한다.
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
		HitResult, GetActorLocation(), GetActorLocation() + GetActorForwardVector() * GetZombieAttackRange(),
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(GetZombieAttackRadius()), Params);
	Params.AddIgnoredActor(this);

	// 디버그 드로잉
	FVector TraceVec = GetActorForwardVector() * GetZombieAttackRange();
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeigh = GetZombieAttackRange() * 0.5f + GetZombieAttackRadius();
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;
	DrawDebugCapsule(GetWorld(), Center, HalfHeigh, 200.0f, CapsuleRot, DrawColor, false, DebugLifeTime);

	if (bResult) // 맞았는가?
	{
		if (HitResult.GetActor()->ActorHasTag("Player")) // 맞은 액터가 플레이어인가?
		{
			UE_LOG(LogTemp, Log, TEXT("Hit Actor Name: %s"), *HitResult.Actor->GetName());
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(GetZombieDamage(), DamageEvent, GetController(), this); // 플레이어에게 데미지를 가한다.
		}
	}
}

// Getter 함수
float AAZombie::GetZombieDamage()
{
	return ZombieDamage;
}
float AAZombie::GetZombieHP()
{
	return Zombie_HP;
}
float AAZombie::GetZombieAttackRange()
{
	return AttackRange;
}
float AAZombie::GetZombieAttackRadius()
{
	return AttackRadius;
}
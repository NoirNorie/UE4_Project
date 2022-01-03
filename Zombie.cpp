// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie.h"

// Sets default values
AZombie::AZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컨트롤러를 사용하도록 설정
	AIControllerClass = AZombieAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	IsAttacking = false; // 비공격상태로 초기화

	// 애니메이션 블루프린트 속성 지정
	static ConstructorHelpers::FClassFinder<UZombieAnim>TZombieAnim(TEXT(
		"AnimBlueprint'/Game/Blueprint/Enemy/Anim_Zombie.Anim_Zombie'")
	);
	if (TZombieAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(TZombieAnim.Class);
	}

	Zombie_HP = 100.0f;
	IsDeath = false;
}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
void AZombie::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ZombieAnimInst = Cast<UZombieAnim>(GetMesh()->GetAnimInstance());
}
void AZombie::Attack()
{
	IsAttacking = true;
	ZombieAnimInst->Attack(); // 공격 모션 동작
}
void AZombie::Detect()
{
	IsDetect = true;
	ZombieAnimInst->Detect(); // 추격 모션 동작
}
void AZombie::OnDetectEnded()
{
	IsDetect = false;
	OnDetectEnd.Broadcast(); // 추적 종료 델리게이트 브로드캐스트
}
void AZombie::OnAttackEnded()
{
	IsAttacking = false;
	OnAttackEnd.Broadcast(); // 공격 종료 델리게이트 브로드캐스트
}

float AZombie::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDeath != true) // 죽으면 데미지를 받지 않게 한다 (엔진 충돌로 인해 게임이 터진다)
	{
		float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Damage %f"), damage));
		Zombie_HP -= damage;
		if (Zombie_HP <= 0)
		{
			Death();
		}

		// 디버그용 메시지
		// UE_LOG(LogClass, Warning, TEXT("Damage: %f"), damage);
		return damage;
	}
	return 0;
}

void AZombie::Death()
{
	GetCharacterMovement()->SetMovementMode(MOVE_None); // 움직임을 멈춘다
	
	IsDeath = true; // 사망 상태를 체크
	ZombieAnimInst->IsDead = true; // 애니메이션에 사망 상태를 알린다.

	GetController()->UnPossess();

	// 애니매이션에서 루프를 멈춰놓아서 쓰러진 상태로 존재한다.
	// 별도의 동작 불필요
	FTimerHandle WaitHandle;
	float WaitTime = 10.0f; // 타이머의 동작 시간
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			Destroy(); // 사망 상태 후 10초 후 액터 소멸
		}), WaitTime, false);	
}
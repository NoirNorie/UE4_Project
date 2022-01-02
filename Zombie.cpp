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

	static ConstructorHelpers::FObjectFinder<UAnimMontage>LoadDieMontage(TEXT(
		"AnimMontage'/Game/Blueprint/Enemy/ZomibeDie.ZomibeDie'")
	);
	if (LoadDieMontage.Succeeded())
	{
		DieMontage = LoadDieMontage.Object;
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
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogClass, Warning, TEXT("Damage: %f"), damage);

	return damage;
}

void AZombie::Death()
{
	//AIControllerClass->ConditionalFinishDestroy();
	GetCharacterMovement()->SetMovementMode(MOVE_None); // 움직임을 멈춘다
	PlayAnimMontage(DieMontage);
	AutoPossessAI = EAutoPossessAI::Disabled;
	
}


//void AZombie::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
//{
//	IsAttacking = false; // 공격이 끝나면 비공격 상태로 전환한다.
//	OnAttackEnd.Broadcast(); // 공격이 종료되었다고 브로드캐스트한다.
//}

//void AZombie::ReceivePointDamage(float Damage, const UDamageType* DamageType, FVector HitLocation, FVector HitNormal,
//	UPrimitiveComponent* HitComponent, FName BoneName, FVector ShotFromDirection, AController* InstigateBy,
//	AActor* DamageCauser, const FHitResult& HitInfo)
//{
//	if (BoneName == TEXT("Character1_Head"))
//	{
//		IsDeath = true;
//		Death();
//	}
//	else
//	{
//		Zombie_HP -= Damage;
//		if (Zombie_HP <= 0)
//		{
//			Death();
//		}
//	}
//}

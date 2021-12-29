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

//void AZombie::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
//{
//	IsAttacking = false; // 공격이 끝나면 비공격 상태로 전환한다.
//	OnAttackEnd.Broadcast(); // 공격이 종료되었다고 브로드캐스트한다.
//}


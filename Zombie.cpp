// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie.h"

// Sets default values
AZombie::AZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��Ʈ�ѷ��� ����ϵ��� ����
	AIControllerClass = AZombieAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	IsAttacking = false; // ����ݻ��·� �ʱ�ȭ

	// �ִϸ��̼� �������Ʈ �Ӽ� ����
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
	ZombieAnimInst->Attack(); // ���� ��� ����
}
void AZombie::Detect()
{
	IsDetect = true;
	ZombieAnimInst->Detect(); // �߰� ��� ����
}
void AZombie::OnDetectEnded()
{
	IsDetect = false;
	OnDetectEnd.Broadcast(); // ���� ���� ��������Ʈ ��ε�ĳ��Ʈ
}
void AZombie::OnAttackEnded()
{
	IsAttacking = false;
	OnAttackEnd.Broadcast(); // ���� ���� ��������Ʈ ��ε�ĳ��Ʈ
}

//void AZombie::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
//{
//	IsAttacking = false; // ������ ������ ����� ���·� ��ȯ�Ѵ�.
//	OnAttackEnd.Broadcast(); // ������ ����Ǿ��ٰ� ��ε�ĳ��Ʈ�Ѵ�.
//}


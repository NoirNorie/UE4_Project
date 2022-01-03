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

float AZombie::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDeath != true) // ������ �������� ���� �ʰ� �Ѵ� (���� �浹�� ���� ������ ������)
	{
		float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Damage %f"), damage));
		Zombie_HP -= damage;
		if (Zombie_HP <= 0)
		{
			Death();
		}

		// ����׿� �޽���
		// UE_LOG(LogClass, Warning, TEXT("Damage: %f"), damage);
		return damage;
	}
	return 0;
}

void AZombie::Death()
{
	GetCharacterMovement()->SetMovementMode(MOVE_None); // �������� �����
	
	IsDeath = true; // ��� ���¸� üũ
	ZombieAnimInst->IsDead = true; // �ִϸ��̼ǿ� ��� ���¸� �˸���.

	GetController()->UnPossess();

	// �ִϸ��̼ǿ��� ������ ������Ƽ� ������ ���·� �����Ѵ�.
	// ������ ���� ���ʿ�
	FTimerHandle WaitHandle;
	float WaitTime = 10.0f; // Ÿ�̸��� ���� �ð�
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			Destroy(); // ��� ���� �� 10�� �� ���� �Ҹ�
		}), WaitTime, false);	
}
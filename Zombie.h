// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// ������ �����Լ� ���
#include "UObject/ConstructorHelpers.h"

// ��������� ���� ��Ʈ�ѷ� ���
#include "ZombieAIController.h"

// ���� �ִϸ��̼� ���
#include "ZombieAnim.h"

#include "Zombie.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate); // ���� ���� ��Ƽĳ��Ʈ ��������Ʈ ����
DECLARE_MULTICAST_DELEGATE(FOnDetectEndDelegate); // ���� ���� ��Ƽĳ��Ʈ ��������Ʈ ����

UCLASS()
class PP_API AZombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombie();
	
	UFUNCTION() void Attack();
	UFUNCTION() void Detect();
	FOnAttackEndDelegate OnAttackEnd; // ������ ����Ǿ��ٴ� ��������Ʈ
	FOnDetectEndDelegate OnDetectEnd; // ������ ����Ǿ��ٴ� ��������Ʈ

	// -- ����--
	UPROPERTY() bool IsAttacking;
	UPROPERTY() bool IsDetect;

	// �ִϸ��̼� �ν��Ͻ� ����
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	class UZombieAnim* ZombieAnimInst;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// �ִϸ��̼� ��¿� �Լ�
	virtual void PostInitializeComponents() override;

	//void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
	UFUNCTION() void OnAttackEnded();
	UFUNCTION() void OnDetectEnded();
};

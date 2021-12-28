// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

// ĳ���� ���
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// ���� ĳ���� ���
#include "Zombie.h"

#include "ZombieAnim.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UZombieAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	// ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float currentPawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float currentWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool DetectTarget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool IsDead;
	
	// �Լ�
	UZombieAnim(); // ������
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION() void Detect();
	UFUNCTION() void Attack();

	// ��Ƽ���� �Լ�
	UFUNCTION() void AnimNotify_AttackEnd();


};

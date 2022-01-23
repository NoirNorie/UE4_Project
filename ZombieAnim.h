// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "ZombieAnim.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UZombieAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	UZombieAnim();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
		float currentPawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
		float currentWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
		bool DetectTarget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
		bool IsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
		bool IsDead;

	UFUNCTION() void Detect();
	UFUNCTION() void Attack();

	UFUNCTION() void AnimNotify_AttackEnd();
	UFUNCTION() void AnimNotify_DetectEnd();

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

// 캐릭터 헤더
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// 좀비 캐릭터 헤더
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
	// 변수
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
	
	// 함수
	UZombieAnim(); // 생성자
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION() void Detect();
	UFUNCTION() void Attack();

	// 노티파이 함수
	UFUNCTION() void AnimNotify_AttackEnd();


};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimInstance.h"

#include "GameFramework/Pawn.h"

// ĳ���� ���
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

// �������̽� ���
#include "TPlayerInterface.h"

// �÷��̾� ĳ���� ���
#include "TPlayer.h"

//// ���� ���
//#include "Engine/Engine.h"

#include "TAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UTAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	// ���� ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsInAir;

	// �ȱ�, �޸��� �� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentWalkSpeed;

	// ���� ������ ����� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool WeaponState;

	// ���ؿ� ����� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool Aiming;

public:
	UTAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};

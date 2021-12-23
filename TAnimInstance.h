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
public:
	// -- ���� --
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn)
		float Direction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn)
		float aim_Pitch;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn)
		float aim_Yaw;

	// �ൿ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsFire; // ��� ���θ� �˸� ����	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsReload; // ������ ���θ� �˸� ����

	// -- ���� --

	// -- ��Ƽ���� ���� --
	UFUNCTION()
	void AnimNotify_FireEnd(); // ��� ���Ḧ �˸� ����
	UFUNCTION()
	void AnimNotify_ReloadEnd();

	// -- ��Ƽ���� ���� --

	// -- �Լ� --
	UFUNCTION() void PlayFire(); // ��� �Լ�
	UFUNCTION() void PlayReload(); // ������ �Լ�

	// -- �Լ� --
public:
	UTAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimInstance.h"

#include "GameFramework/Pawn.h"

// 캐릭터 헤더
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

// 인터페이스 헤더
#include "TPlayerInterface.h"

// 플레이어 캐릭터 헤더
#include "TPlayer.h"

//// 엔진 헤더
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
	// -- 변수 --
	// 점프 판정용 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsInAir;
	// 걷기, 달리기 용 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentWalkSpeed;

	// 무기 장착에 사용할 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool WeaponState;

	// 조준에 사용할 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool Aiming;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn)
		float Direction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn)
		float aim_Pitch;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn)
		float aim_Yaw;

	// 행동 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsFire; // 사격 여부를 알릴 변수	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsReload; // 재장전 여부를 알릴 변수

	// -- 변수 --

	// -- 노티파이 변수 --
	UFUNCTION()
	void AnimNotify_FireEnd(); // 사격 종료를 알릴 변수
	UFUNCTION()
	void AnimNotify_ReloadEnd();

	// -- 노티파이 변수 --

	// -- 함수 --
	UFUNCTION() void PlayFire(); // 사격 함수
	UFUNCTION() void PlayReload(); // 재장전 함수

	// -- 함수 --
public:
	UTAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};

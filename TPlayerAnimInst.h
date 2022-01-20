// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

// 캐릭터 인터페이스 함수
#include "TPlayerInterface.h"

#include "TPlayerAnimInst.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UTPlayerAnimInst : public UAnimInstance
{
	GENERATED_BODY()

public:
	// 이동 관련 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsInAir;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsMoving;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentWalkSpeed;

	// 무기 장착 여부 판정
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool WeaponState;

	// 조준 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool Aiming;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn)
		float Direction;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn)
		float aim_Pitch;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn)
		float aim_Yaw;

	// 사격 상태
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsFire;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsReload;
	// 사격음 큐와 컴포넌트
	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class USoundCue* ShotCue;
	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class UAudioComponent* ShotCueComponent;

	UFUNCTION() void PlayFire();
	UFUNCTION() void PlayReload();


	// 노티파이 함수
	UFUNCTION() void AnimNotify_FireStart(); // 사격 시작 함수
	UFUNCTION() void AnimNotify_FireEnd(); // 사격 종료 함수
	UFUNCTION() void AnimNotify_ReloadEnd(); // 재장전 종료 함수

	// 사격음 변수
	int32 ShotIDX;

public:
	UTPlayerAnimInst(); // 생성자
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};

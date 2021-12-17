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
private:
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

public:
	UTAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};

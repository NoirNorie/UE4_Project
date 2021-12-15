// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UTAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;


public:
	UTAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};

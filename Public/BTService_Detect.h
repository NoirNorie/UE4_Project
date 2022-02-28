// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"

#include "TPlayer.h"
#include "AZombie.h"
#include "ZombieController.h"
#include "BehaviorTree/BlackboardComponent.h"
// 디버그 헤더
#include "DrawDebugHelpers.h"

#include "BTService_Detect.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()
private:
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectRadius;
public:
	UBTService_Detect();
	float Aggro();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

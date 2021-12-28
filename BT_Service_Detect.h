// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"

// 플레이어 헤더
#include "TPlayer.h"
// 좀비 헤더
#include "Zombie.h"
// 좀비 컨트롤러 헤더
#include "ZombieAIController.h"
// 블랙보드 컴포넌트 헤더
#include "BehaviorTree/BlackboardComponent.h"
//// 디버그용 헤더
//#include "DrawDebugHelpers.h"
#include "BT_Service_Detect.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UBT_Service_Detect : public UBTService
{
	GENERATED_BODY()
public:
	UBT_Service_Detect();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

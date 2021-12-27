// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "TPlayer.h"
#include "ZombieAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "BT_Decorator_IsInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UBT_Decorator_IsInAttackRange : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBT_Decorator_IsInAttackRange();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};

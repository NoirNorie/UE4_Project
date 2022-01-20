// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "TPlayer.h"
#include "ZombieController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "BTDecorator_IsInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UBTDecorator_IsInAttackRange : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_IsInAttackRange();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};

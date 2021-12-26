// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "ZombieAIController.h"

//// �����̺�� Ʈ���� ������ ���
//#include "BehaviorTree/BehaviorTree.h"
//#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "NavigationSYstem.h"


#include "BT_Task_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UBT_Task_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBT_Task_FindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "Zombie.h"
#include "ZombieAIController.h"

#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "BT_Task_Attack.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UBT_Task_Attack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBT_Task_Attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite) class AZombie* m_pZombie;

	UPROPERTY() bool IsAttacking;
	//UFUNCTION() void CallDeleFunc_AttackEnd(); // 공격 종료를 알릴 델리게이트 호출 함수

};

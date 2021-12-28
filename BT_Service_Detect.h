// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"

// �÷��̾� ���
#include "TPlayer.h"
// ���� ���
#include "Zombie.h"
// ���� ��Ʈ�ѷ� ���
#include "ZombieAIController.h"
// ������ ������Ʈ ���
#include "BehaviorTree/BlackboardComponent.h"
//// ����׿� ���
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

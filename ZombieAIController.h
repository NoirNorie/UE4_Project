// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"

// ������ �����Լ� ���
#include "UObject/ConstructorHelpers.h"
// �����̺�� Ʈ���� ������ ���
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
// �����̺��Ʈ�� ������Ʈ ���
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class PP_API AZombieAIController : public AAIController
{
	GENERATED_BODY()
public:
	// ������
	AZombieAIController();
	
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetPosKey;

	UFUNCTION() 
	virtual void OnPossess(APawn* InPawn) override;

	void RunAI();
	void StopAI();

	// ������
	UPROPERTY() 
	class UBlackboardData* BBZombie;
	// �����̺�� Ʈ��
	UPROPERTY() 
	class UBehaviorTree* BTZombie;
};

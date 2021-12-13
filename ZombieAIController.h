// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

// �ΰ����� ���� ���
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

// ������ �� ����� �Լ��� ����ִ� ���
#include "UObject/ConstructorHelpers.h"

#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AZombieAIController : public AAIController
{
	GENERATED_BODY()
public:
	AZombieAIController();

	// ������ Ű ���ε�
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BDAsset;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"

#include "UObject/ConstructorHelpers.h"

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

	UFUNCTION() 
	virtual void OnPossess(APawn* InPawn) override;

	// ������
	UPROPERTY() 
	class UBlackboardData* BBZombie;
	// �����̺�� Ʈ��
	UPROPERTY() 
	class UBehaviorTree* BTZombie;
};

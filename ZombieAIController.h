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
	// 생성자
	AZombieAIController();
	
	static const FName HomePosKey;
	static const FName PatrolPosKey;

	UFUNCTION() 
	virtual void OnPossess(APawn* InPawn) override;

	// 블랙보드
	UPROPERTY() 
	class UBlackboardData* BBZombie;
	// 비헤이비어 트리
	UPROPERTY() 
	class UBehaviorTree* BTZombie;
};

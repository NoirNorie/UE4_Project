// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"

// 생성자 보조함수 헤더
#include "UObject/ConstructorHelpers.h"
// 비헤이비어 트리와 블랙보드 헤더
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
// 비헤이비어트리 컴포넌트 헤더
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
	// 생성자
	AZombieAIController();
	
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetPosKey;

	UFUNCTION() 
	virtual void OnPossess(APawn* InPawn) override;

	void RunAI();
	void StopAI();

	// 블랙보드
	UPROPERTY() 
	class UBlackboardData* BBZombie;
	// 비헤이비어 트리
	UPROPERTY() 
	class UBehaviorTree* BTZombie;
};

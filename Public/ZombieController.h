// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

// 생성자 보조 함수
#include "UObject/ConstructorHelpers.h"

// 비헤이비어 트리 헤더
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "ZombieController.generated.h"

/**
 * 
 */
UCLASS()
class PP_API AZombieController : public AAIController
{
	GENERATED_BODY()
public:
	AZombieController();

	UFUNCTION()
		virtual void OnPossess(APawn* InPawn) override;
	UFUNCTION()
	void SetDetectRadius(float radius);
	UFUNCTION()
	float GetDetectRadius();
	UFUNCTION()
	void ResetDetectRadius();

	void RunAI();
	void StopAI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float detectRadius;
	UPROPERTY() class UBlackboardData* BBZombie;
	UPROPERTY() class UBehaviorTree* BTZombie;
public:
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetPosKey;
};

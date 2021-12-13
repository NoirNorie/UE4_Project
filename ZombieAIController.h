// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

// 인공지능 관련 헤더
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

// 생성자 중 사용할 함수가 들어있는 헤더
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

	// 블랙보드 키 바인딩
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BDAsset;
	
};

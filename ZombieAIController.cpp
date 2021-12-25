// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"

const FName AZombieAIController::HomePosKey(TEXT("HomePos"));
const FName AZombieAIController::PatrolPosKey(TEXT("PatrolPos"));

AZombieAIController::AZombieAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(
		TEXT("BlackboardData'/Game/Blueprint/Enemy/BB_Zombie.BB_Zombie'")
	); // AI 블랙보드
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(
		TEXT("BehaviorTree'/Game/Blueprint/Enemy/BT_Zombie.BT_Zombie'")
	);
	if (BBObject.Succeeded())
	{
		BBZombie = BBObject.Object;
	}
	if (BTObject.Succeeded())
	{
		BTZombie = BTObject.Object;
	}
}

void AZombieAIController::OnPossess(APawn* InPawn)
{
	Super::Possess(InPawn);
	if (UseBlackboard(BBZombie, Blackboard))
	{
		RunBehaviorTree(BTZombie);
	}
}
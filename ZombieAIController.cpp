// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"

const FName AZombieAIController::HomePosKey(TEXT("HomePos"));
const FName AZombieAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AZombieAIController::TargetPosKey(TEXT("TargetPos"));

AZombieAIController::AZombieAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(
		TEXT("BlackboardData'/Game/Blueprint/Enemy/BB_Zombie.BB_Zombie'")
	);
	if (BBObject.Succeeded())
	{
		BBZombie = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(
		TEXT("BehaviorTree'/Game/Blueprint/Enemy/BT_Zombie.BT_Zombie'")
	);
	if (BTObject.Succeeded())
	{
		BTZombie = BTObject.Object;
	}
}

void AZombieAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (UseBlackboard(BBZombie, Blackboard))
	{
		RunBehaviorTree(BTZombie);
	}
	//RunAI();
}

void AZombieAIController::RunAI()
{
	if (UseBlackboard(BBZombie, Blackboard))
	{
		RunBehaviorTree(BTZombie);
	}
}

void AZombieAIController::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent == nullptr)
	{
		return;
	}
	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}
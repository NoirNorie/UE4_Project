// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieController.h"

const FName AZombieController::HomePosKey(TEXT("HomePos"));
const FName AZombieController::PatrolPosKey(TEXT("PatrolPos"));
const FName AZombieController::TargetPosKey(TEXT("TargetPos"));

AZombieController::AZombieController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(
		TEXT("BlackboardData'/Game/Blueprint/Zombie/BehaviorTree/BB_Zombie.BB_Zombie'"));
	if (BBObject.Succeeded())
	{
		BBZombie = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(
		TEXT("BehaviorTree'/Game/Blueprint/Zombie/BehaviorTree/BT_Zombie.BT_Zombie'"));
	if (BTObject.Succeeded())
	{
		BTZombie = BTObject.Object;
	}
}

void AZombieController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (UseBlackboard(BBZombie, Blackboard))
	{
		RunBehaviorTree(BTZombie);
	}
}

void AZombieController::RunAI()
{
	if (UseBlackboard(BBZombie, Blackboard))
	{
		RunBehaviorTree(BTZombie);
	}
}

void AZombieController::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent == nullptr) return;
	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}
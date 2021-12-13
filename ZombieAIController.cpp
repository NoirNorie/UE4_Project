// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"

const FName AZombieAIController::HomePosKey(TEXT("HomePos"));
const FName AZombieAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AZombieAIController::TargetKey(TEXT("Target"));

AZombieAIController::AZombieAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BDObject(TEXT("BlackboardData'/Game/Blueprints/BD_Zombie.BD_Zombie'"));
	if (BDObject.Succeeded())
	{
		BDAsset = BDObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/Blueprints/BT_Zombie.BT_Zombie'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}
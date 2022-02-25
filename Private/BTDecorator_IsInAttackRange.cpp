// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return false;

	ATPlayer* Target = Cast<ATPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AZombieController::TargetPosKey));
	if (Target == nullptr) return false;

	bool bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);
	return bResult;
}
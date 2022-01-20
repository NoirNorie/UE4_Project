// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Zombie = Cast<AAZombie>(OwnerComp.GetAIOwner()->GetPawn());
	if (Zombie == nullptr) return EBTNodeResult::Failed;

	auto Target = Cast<ATPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AZombieController::TargetPosKey));
	if (Target == nullptr) return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - Zombie->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRotation = FRotationMatrix::MakeFromX(LookVector).Rotator();
	Zombie->SetActorRotation(FMath::RInterpTo(Zombie->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
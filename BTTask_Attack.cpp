// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Zombie = Cast<AAZombie>(OwnerComp.GetAIOwner()->GetPawn());
	if (Zombie == nullptr) return EBTNodeResult::Failed;

	Zombie->Attack();
	IsAttacking = true;
	Zombie->OnAttackEnd.AddLambda([this]()->void {IsAttacking = false; });

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	auto Zombie = Cast<AAZombie>(OwnerComp.GetAIOwner()->GetPawn());
	if (Zombie->IsAttacking == false)
	{
		IsAttacking = false;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

}
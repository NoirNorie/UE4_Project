// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_Attack.h"

UBT_Task_Attack::UBT_Task_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
	//m_pZombie->OnAttackEnd.AddUFunction(this, FName("CallDeleFunc_AttackEnd")); // 공격 종료 바인드
}

EBTNodeResult::Type UBT_Task_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Zombie = Cast<AZombie>(OwnerComp.GetAIOwner()->GetPawn());
	if (Zombie == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	Zombie->Attack();
	IsAttacking = true;
	Zombie->OnAttackEnd.AddLambda([this]()->void {IsAttacking = false; });
	
	
	return EBTNodeResult::InProgress;

}

void UBT_Task_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// 좀비 값을 읽어온다.
	auto Zombie = Cast<AZombie>(OwnerComp.GetAIOwner()->GetPawn());
	if (Zombie == nullptr) return;

	if (Zombie->IsAttacking == false)
	{
		IsAttacking = false;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	//IsAttacking = false;
	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
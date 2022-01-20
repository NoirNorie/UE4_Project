// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.0f;
	if (World == nullptr) return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults, Center, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);



	if (bResult)
	{
		for (FOverlapResult OverlapResult : OverlapResults)
		{
			ATPlayer* aPlayer = Cast<ATPlayer>(OverlapResult.GetActor());
			if (aPlayer && (aPlayer->GetController()->IsPlayerController()))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AZombieController::TargetPosKey, aPlayer);

				// 일단 폰을 제어하고 있는 무언가가 널포인터가 아닌것이 위에서 확실하므로
				AAZombie* Zombie = Cast<AAZombie>(ControllingPawn);
				if (Zombie != nullptr) Zombie->Detect();


				if (ControllingPawn->GetDistanceTo(aPlayer) >= 850.0f)
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(AZombieController::TargetPosKey, nullptr);
				}
				return;
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AZombieController::TargetPosKey, nullptr);
		return;
	}
}
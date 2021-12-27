// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_Detect.h"

UBT_Service_Detect::UBT_Service_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBT_Service_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.0f; // 감지 범위가 600의 반지름인 구체
	
	if (World == nullptr) return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	// 오브젝트가 감지가 되면, 그 오브젝트가 Character인지 검사한다.
	if (bResult)
	{
		for (FOverlapResult OverlapResult : OverlapResults)
		{
			ATPlayer* aPlayer = Cast<ATPlayer>(OverlapResult.GetActor());
			if (aPlayer && aPlayer->GetController()->IsPlayerController())
			{
				// Character면, 블랙보드에 저장한다.
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AZombieAIController::TargetPosKey, aPlayer);
				//OwnerComp.GetBlackboardComponent()->SetValueAsVector(AZombieAIController::TargetPosKey, aPlayer);

				return;
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AZombieAIController::TargetPosKey, nullptr);
	}


}
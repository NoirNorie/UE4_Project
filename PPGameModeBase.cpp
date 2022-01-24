// Copyright Epic Games, Inc. All Rights Reserved.


#include "PPGameModeBase.h"

APPGameModeBase::APPGameModeBase(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	// 위젯 읽어오기
	static ConstructorHelpers::FClassFinder<UTPlayerStateWidget> PlayerStateWidgetAsset(
		TEXT("/Game/Blueprint/Widget/PlayerWidget")
	);
	if (PlayerStateWidgetAsset.Succeeded())
	{
		PlayerStateWidgetClass = PlayerStateWidgetAsset.Class;
	}
}

void APPGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Game Start"));
	}

	// 위젯 배치
	if (IsValid(PlayerStateWidgetClass))
	{
		PlayerStateWidget = Cast<UTPlayerStateWidget>(CreateWidget(GetWorld(), PlayerStateWidgetClass));

		if (IsValid(PlayerStateWidget))
		{
			PlayerStateWidget->AddToViewport();
		}
	}

}

UTPlayerStateWidget* APPGameModeBase::GetPlayerStateWidget() const
{
	return PlayerStateWidget;
}
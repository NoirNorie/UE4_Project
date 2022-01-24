// Copyright Epic Games, Inc. All Rights Reserved.


#include "PPGameModeBase.h"

void APPGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Game Start"));
	}

}

void APPGameModeBase::BeginPlay()
{

	// 위젯 읽어오기
	static ConstructorHelpers::FClassFinder<UTPlayerStateWidget> PlayerStateWidgetAsset(
		TEXT("WidgetBlueprint'/Game/Blueprint/Widget/PlayerWidget.PlayerWidget'")
	);
	if (PlayerStateWidgetAsset.Succeeded())
	{
		PlayerStateWidgetClass = PlayerStateWidgetAsset.Class;
	}

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
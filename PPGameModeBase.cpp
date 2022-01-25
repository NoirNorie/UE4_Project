// Copyright Epic Games, Inc. All Rights Reserved.


#include "PPGameModeBase.h"

APPGameModeBase::APPGameModeBase(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	//// 위젯 읽어오기
	//static ConstructorHelpers::FClassFinder<UTPlayerStateWidget> PlayerStateWidgetAsset(
	//	TEXT("/Game/Blueprint/Widget/PlayerWidget")
	//);

	//if (PlayerStateWidgetAsset.Succeeded())
	//{
	//	PlayerStateWidgetClass = PlayerStateWidgetAsset.Class;
	//}
}

void APPGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Game Start"));
	}
	ChangeMenuWidget(StartWidgetClass);

}

void APPGameModeBase::ChangeMenuWidget(TSubclassOf<UTPlayerStateWidget>NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UTPlayerStateWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}

}
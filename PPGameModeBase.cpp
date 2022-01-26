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

//void APPGameModeBase::StartPlay()
//{
//	Super::StartPlay();
//
//	if (GEngine)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Game Start"));
//	}
//}

void APPGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Begin Start"));
	}
	CreateStateWidget(StartWidgetClass);
}

void APPGameModeBase::CreateStateWidget(TSubclassOf<UTPlayerStateWidget>NewWidgetClass)
{
	if (CurrentWidget != nullptr) // 띄워진 위젯이 있다면
	{

		CurrentWidget->RemoveFromViewport(); // 위젯을 지운다.
		CurrentWidget = nullptr;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("RemoveWidget")));
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UTPlayerStateWidget>(GetWorld(), NewWidgetClass);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("LocateWidget")));
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport(); // 위젯을 띄운다.
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AddWidget")));
		}
	}

}

// 띄워진 위젯을 반환하는 함수
UTPlayerStateWidget* APPGameModeBase::GetPlayerStateWidget() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("return Widget")));
	return CurrentWidget;
}
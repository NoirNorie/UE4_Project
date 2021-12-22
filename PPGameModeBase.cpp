// Copyright Epic Games, Inc. All Rights Reserved.


#include "PPGameModeBase.h"

//void APPGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
//{
//	//if (CurrentWidget != nullptr) // 보여지고 있던 위젯이 있다면
//	//{
//	//	CurrentWidget->RemoveFromViewport(); // 이전 위젯을 지운다.
//	//	CurrentWidget = nullptr; // 위젯을 비움
//	//}
//
//	//if (NewWidgetClass) // 불러올 위젯이 있다면
//	//{
//	//	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
//	//	if (CurrentWidget != nullptr)
//	//	{
//	//		CurrentWidget->AddToViewport(); // 뷰 포트에 추가한다.
//	//	}
//	//}
//}

void APPGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//CreatePlayerWidget(StartingWidgetClass);
	if (Player_StatusWidget)
	{
		StatusWidget = CreateWidget<UTPlayerWidget>(GetWorld(), Player_StatusWidget);
		if (StatusWidget)
		{
			StatusWidget->AddToViewport();
		}
	}
}

//void APPGameModeBase::CreatePlayerWidget(TSubclassOf<UUserWidget> NewWidgetClass)
//{
//	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
//	if (CurrentWidget)
//	{
//		CurrentWidget->AddToViewport();
//	}
//
//	//PlayerStateWidget->AddToViewport();
//	//UUserWidget* PlayerState = LoadObject<UUserWidget>();
//	//PlayerState->AddToViewport();
//}
// Copyright Epic Games, Inc. All Rights Reserved.


#include "PPGameModeBase.h"

//void APPGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
//{
//	//if (CurrentWidget != nullptr) // �������� �ִ� ������ �ִٸ�
//	//{
//	//	CurrentWidget->RemoveFromViewport(); // ���� ������ �����.
//	//	CurrentWidget = nullptr; // ������ ���
//	//}
//
//	//if (NewWidgetClass) // �ҷ��� ������ �ִٸ�
//	//{
//	//	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
//	//	if (CurrentWidget != nullptr)
//	//	{
//	//		CurrentWidget->AddToViewport(); // �� ��Ʈ�� �߰��Ѵ�.
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
// Copyright Epic Games, Inc. All Rights Reserved.


#include "PPGameModeBase.h"

void APPGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (Player_StatusWidget) // �⺻ ���� ���
	{
		StatusWidget = CreateWidget<UTPlayerWidget>(GetWorld(), Player_StatusWidget);
		if (StatusWidget)
		{
			StatusWidget->AddToViewport();
		}
	}
}
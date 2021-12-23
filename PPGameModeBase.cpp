// Copyright Epic Games, Inc. All Rights Reserved.


#include "PPGameModeBase.h"

void APPGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (Player_StatusWidget) // 기본 위젯 출력
	{
		StatusWidget = CreateWidget<UTPlayerWidget>(GetWorld(), Player_StatusWidget);
		if (StatusWidget)
		{
			StatusWidget->AddToViewport();
		}
	}
}
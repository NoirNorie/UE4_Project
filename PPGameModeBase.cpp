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
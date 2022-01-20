// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PP_API APPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	virtual void StartPlay() override;
};

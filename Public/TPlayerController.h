// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Blueprint/UserWidget.h"
#include "TPlayerStateWidget.h"
#include "TPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PP_API ATPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

protected:
	virtual void BeginPlay() override;
};

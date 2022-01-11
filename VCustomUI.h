// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPlayer.h"
#include "VCustomUI.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UVCustomUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UVCustomUI(const FObjectInitializer& ObjectInitializer);

	virtual void Init() {};
public:
	ATPlayer* Player;
};

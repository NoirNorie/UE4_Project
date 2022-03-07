// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "PPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UPPGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPPGameInstance();

	virtual void Init() override;
	FStreamableManager StreamableManager;

	
};

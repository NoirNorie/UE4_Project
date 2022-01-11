// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VCustomUI.h"
#include "VGameUI.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UVGameUI : public UVCustomUI
{
	GENERATED_BODY()
public:
	UVGameUI(const FObjectInitializer& ObjectInitializer);
	void Init() override;
public:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	//class UVInventory* Inventory;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UInventory : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
};

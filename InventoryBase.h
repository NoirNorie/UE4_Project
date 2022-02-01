// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryData.h"

#include "Components/ListView.h"

#include "InventoryBase.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UInventoryBase : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), category = "Player State UI")
		class UListView* List;


public:
	UInventoryBase(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	void InventoryInit();
};
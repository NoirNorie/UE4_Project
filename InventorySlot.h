// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "InventoryData.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UInventorySlot : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"), category = "Inventory")
		int32 ItemIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"), category = "Inventory")
		int32 ItemNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"), category = "Inventory")
		int32 ItemCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"), category = "Inventory")
		FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"), category = "Inventory")
		UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* ItemNameBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* ItemCountBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UImage* ImgBox;

public:

	UFUNCTION(BlueprintCallable)
		void SetData(class UInventoryData* Data);

	// Setter
	void SetItemIndex(int32 idx);
	void SetItemNumber(int32 num);
	void SetItemCount(int32 cnt);
	void SetItemName(FString name);
	void SetItemIcon(UTexture2D* Icon);
	//// Getter
	//int32 GetItemIndex();
	//int32 GetItemNumber();
	//int32 GetItemCount();
	//FString GetItemName();
	//UTexture2D* GetItemIcon();


};

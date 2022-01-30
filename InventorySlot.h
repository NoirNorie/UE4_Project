// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryData.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UInventorySlot : public UUserWidget
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

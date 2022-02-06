// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryData.h"

// 생성자 보조 함수 헤더
#include "UObject/ConstructorHelpers.h"

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

	// 인벤토리에 들어간 정보를 담고 있을 Map
	TMap<FName, int32> InventoryMap;
	int32 currentIndex;

public:
	virtual void NativeConstruct() override;

	void InventoryInit();

	void ItemInsert(FName ItemName);
	void ItemDelete(FName ItemName);

	void AmmoItemSelector(int32 t);
	void FoodItemSelector(int32 t);
};
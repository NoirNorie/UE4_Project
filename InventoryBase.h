// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryData.h"
#include "InventorySlot.h"

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

	// 인벤토리에 들어간 정보를 담고 있을 Set
	TSet<FName> InventorySet;

public:
	virtual void NativeConstruct() override;

	void InventoryInit();

	void ItemClick(UObject* items);

	void ItemInsert(FName ItemName);
	void ItemDelete(FName ItemName);


	void AmmoInserter(FName AmmoName, int32 AmmoType);
	void AmmoItemSelector(int32 t);
	void FoodInserter(FName FoodName, float hungry, float thirst, int32 FoodType);
	void FoodItemSelector(int32 t, float hungry, float thirst);


	int32 HaveAmmo(FName AmmoName); // 해당 총알이 인벤토리에 존재하는지 물어보는 함수
	void ReloadAmmo(FName AmmoName);
};
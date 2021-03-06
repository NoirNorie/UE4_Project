// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryData.generated.h"

// 아이템의 정보를 저장하는 클래스
// 일반적으로 UObject는 블루프린트로 만들 수 없다
// 특별하게 지정하려고 하거나 블루프린트 상에서 나타내기 위해서는
// UCLASS() 매크로에 Blueprintable, BlueprintType 지정자를 집어넣으면 된다.

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PP_API UInventoryData : public UObject
{
	GENERATED_BODY()
public:
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item Stat")
		float dec_Hungry;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item Stat")
		float dec_Thirst;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item Stat")
		float inc_HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item Stat")
		float ItemWeight;

public:
	// Setter
	void SetItemIndex(int32 idx);
	void SetItemNumber(int32 num);
	void SetItemCount(int32 cnt);
	void SetItemName(FString name);
	void SetItemIcon(const FString& IconPath);

	// item stat setter
	void SetItemDecHungry(float inp);
	void SetItemDecThrist(float inp);
	void SetItemIncHP(float inp);
	void SetItemWeight(float inp);

	// Getter
	int32 GetItemIndex();
	int32 GetItemNumber();
	int32 GetItemCount();
	FString GetItemName();
	UTexture2D* GetItemIcon();

	// item stat getter
	float GetDecHungry();
	float GetDecThrist();
	float GetIncHP();
	float GetWeight();
};

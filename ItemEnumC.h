// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
//class PP_API ItemEnumC
//{
//public:
//	ItemEnumC();
//	~ItemEnumC();
//};

// �κ��丮 ������ ������ ������
UENUM(BlueprintType)
enum ESlotType
{
	SLOT_None		UMETA(DisplayName = "None"),
	SLOT_Item		UMETA(DisplayName = "Item"),
	SLOT_Mag		UMETA(DisplayName = "Magazine"),
	SLOT_Food		UMETA(DisplayName = "Food"),
	SLOT_Drink		UMETA(DisplayName = "Drink")
};
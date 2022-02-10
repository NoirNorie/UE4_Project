// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryData.h"

// Setter
void UInventoryData::SetItemIndex(int32 idx)
{
	ItemIndex = idx;
}
void UInventoryData::SetItemNumber(int32 num)
{
	ItemNumber = num;
}
void UInventoryData::SetItemCount(int32 cnt)
{
	ItemCount = cnt;
}
void UInventoryData::SetItemName(FString name)
{
	ItemName = name;
}
void UInventoryData::SetItemIcon(const FString& IconPath)
{
	ItemIcon = LoadObject<UTexture2D>(nullptr, *IconPath);

}

void UInventoryData::SetItemDecHungry(float inp)
{
	dec_Hungry = inp;
}
void UInventoryData::SetItemDecThrist(float inp)
{
	dec_Thirst = inp;
}
void UInventoryData::SetItemIncHP(float inp)
{
	inc_HP = inp;
}
void UInventoryData::SetItemWeight(float inp)
{
	ItemWeight = inp;
}


// Getter
int32 UInventoryData::GetItemIndex()
{
	return ItemIndex;
}
int32 UInventoryData::GetItemNumber()
{
	return ItemNumber;
}
int32 UInventoryData::GetItemCount()
{
	return ItemCount;
}
FString UInventoryData::GetItemName()
{
	return ItemName;
}
UTexture2D* UInventoryData::GetItemIcon()
{
	return ItemIcon;
}

float UInventoryData::GetDecHungry()
{
	return dec_Hungry;
}
float UInventoryData::GetDecThrist()
{
	return dec_Thirst;
}
float UInventoryData::GetIncHP()
{
	return inc_HP;
}
float UInventoryData::GetWeight()
{
	return ItemWeight;
}
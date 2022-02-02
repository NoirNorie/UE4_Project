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
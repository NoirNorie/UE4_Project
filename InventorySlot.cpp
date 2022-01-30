// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"

	// Setter
void UInventorySlot::SetItemIndex(int32 idx)
{
	ItemIndex = idx;
}
void UInventorySlot::SetItemNumber(int32 num)
{
	ItemNumber = num;
}
void UInventorySlot::SetItemCount(int32 cnt)
{
	ItemCount = cnt;
}
void UInventorySlot::SetItemName(FString name)
{
	ItemName = name;
}
void UInventorySlot::SetItemIcon(UTexture2D* Icon)
{
	ItemIcon = Icon;
}
//// Getter
//int32 UInventorySlot::GetItemIndex()
//{
//
//}
//int32 UInventorySlot::GetItemNumber()
//{
//
//}
//int32 UInventorySlot::GetItemCount()
//{
//
//}
//FString UInventorySlot::GetItemName()
//{
//
//}
//UTexture2D* UInventorySlot::GetItemIcon()
//{
//
//}


void UInventorySlot::SetData(class UInventoryData* Data)
{
	SetItemIndex(Data->GetItemIndex());
	SetItemCount(Data->GetItemCount());
	SetItemName(Data->GetItemName());
}
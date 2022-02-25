// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
}

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
	ItemCountBox->SetText(FText::FromString(FString::FromInt(ItemCount)));
}
void UInventorySlot::SetItemName(FString name)
{
	ItemName = name;
	ItemNameBox->SetText(FText::FromString(ItemName));
}
void UInventorySlot::SetItemIcon(UTexture2D* Icon)
{
	ItemIcon = Icon;
	ImgBox->SetBrushFromTexture(ItemIcon);
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
	SetItemIcon(Data->GetItemIcon());
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "VSlot.h"

void UVSlot::Init()
{
	Refresh();
}
void UVSlot::setType(ESlotType type)
{
	Type = type;
}
void UVSlot::setTexture(UTexture2D* tex)
{
	if (tex == nullptr) return;

	Img->SetBrushFromTexture(tex);
}
void UVSlot::Refresh()
{
	switch (Type)
	{
		case ESlotType::SLOT_Item:
		{
			FItemData& data = Player->Inventory[SlotNum];

			if (data.Texture != nullptr)
			{
				setTexture(data.Texture);
			}
			Count = data.Count;

			if (Count <= 1)
			{
				Text->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				Text->SetVisibility(ESlateVisibility::Visible);
				Text->SetText(FText::FromString(FString::FromInt(Count)));
			}
			break;
		}	
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInteractionWidget.h"

void UItemInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 각 위젯의 내용을 초기화하고 연결해놓는다.
	ItemName = "TMP";
	InteractionKey = "E";
	Percent = 0.0f;
	
	ItemNameBox = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemNameBox")));
	InteractionKeyBox = Cast<UTextBlock>(GetWidgetFromName(TEXT("InteractionKeyBox")));
	InteractionProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("InteractionProgressBar")));
}


void UItemInteractionWidget::SetItemName(FString itemName)
{
	if (IsValid(ItemNameBox))
	{
		ItemNameBox->SetText(FText::FromString(itemName));
	}
}
void UItemInteractionWidget::SetKeyName(FString keyName)
{
	if (IsValid(InteractionKeyBox))
	{
		InteractionKeyBox->SetText(FText::FromString(keyName));
	}
}
void UItemInteractionWidget::SetPercent(float percent)
{
	if (IsValid(InteractionProgressBar))
	{
		InteractionProgressBar->SetPercent(percent / 100);
	}
}
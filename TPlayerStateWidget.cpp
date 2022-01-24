// Fill out your copyright notice in the Description page of Project Settings.


#include "TPlayerStateWidget.h"

UTPlayerStateWidget::UTPlayerStateWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// 변수 초기화
	UI_WeaponName = "No Weapon";
	UI_CurrentAmmo = "0";
	UI_RemainAmmo = "0";

	UI_HP = 100.0f;;
	UI_HungryBar = 0.0f;
	UI_ThirstBar = 0.0f;
}

void UTPlayerStateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	WeaponNameBox = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeaponNameBox")));

	//WeaponNameBox->SetText(FText::FromName(UI_WeaponName));
	//CurrentAmmoBox->SetText(FText::FromName(UI_CurrentAmmo));
	//RemainAmmoBox->SetText(FText::FromName(UI_RemainAmmo));
	//HPBar->SetPercent(UI_HP);
	//HungryBar->SetPercent(UI_HungryBar);
	//ThirstBar->SetPercent(UI_ThirstBar);
}

void UTPlayerStateWidget::SetWeaponName(FName WName)
{
	if (IsValid(WeaponNameBox))
	{
		WeaponNameBox->SetText(FText::FromName(WName));
	}
}
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
	CurrentAmmoBox = Cast<UTextBlock>(GetWidgetFromName(TEXT("CurrentAmmoBox")));
	RemainAmmoBox = Cast<UTextBlock>(GetWidgetFromName(TEXT("RemainAmmoBox")));
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	HungryBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HungryBar")));
	ThirstBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ThirtBar")));
}

// Set 함수
void UTPlayerStateWidget::SetWeaponName(FName WName)
{
	if (IsValid(WeaponNameBox))
	{
		WeaponNameBox->SetText(FText::FromName(WName));
	}
}
void UTPlayerStateWidget::SetCurrentAmmo(int32 ammo)
{
	if (IsValid(CurrentAmmoBox))
	{
		CurrentAmmoBox->SetText(FText::FromString(FString::FromInt(ammo)));
	}
}
void UTPlayerStateWidget::SetRemainAmmo(int32 ammo)
{
	if (IsValid(RemainAmmoBox))
	{
		RemainAmmoBox->SetText(FText::FromString(FString::FromInt(ammo)));
	}
}
void UTPlayerStateWidget::SetCurrentHP(float hp)
{
	if (IsValid(HPBar))
	{
		HPBar->SetPercent(hp);
	}
}
void UTPlayerStateWidget::SetCurrentHungry(float hungry)
{
	if (IsValid(HungryBar))
	{
		HungryBar->SetPercent(hungry);
	}
}
void UTPlayerStateWidget::SetCurrentThirst(float thirst)
{
	if (IsValid(ThirstBar))
	{
		ThirstBar->SetPercent(thirst);
	}
}
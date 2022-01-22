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
	//UBlueprintGeneratedClass* Widget_PlayerState = LoadObject<UBlueprintGeneratedClass>(
	//	nullptr, TEXT("WidgetBlueprint'/Game/Blueprint/Widget/PlayerWidget.PlayerWidget'")
	//);
	//Widget_Status = Cast<UClass>(Widget_PlayerState);

	WeaponName = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeaponName")));
	WeaponName->SetText(FText::FromName(UI_WeaponName));

	CurrentAmmo = Cast<UTextBlock>(GetWidgetFromName(TEXT("CurrentAmmo")));
	CurrentAmmo->SetText(FText::FromName(UI_CurrentAmmo));

	Remain = Cast<UTextBlock>(GetWidgetFromName(TEXT("Remain")));
	Remain->SetText(FText::FromName(UI_RemainAmmo));

	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	HPBar->SetPercent(UI_HP);

	HungryBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HungryBar")));
	HungryBar->SetPercent(UI_HungryBar);

	ThirstBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ThirstBar")));
	ThirstBar->SetPercent(UI_ThirstBar);
}
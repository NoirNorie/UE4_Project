// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	BT_Start = Cast<UButton>(GetWidgetFromName(TEXT("BT_Start")));
	BT_Exit = Cast<UButton>(GetWidgetFromName(TEXT("BT_Exit")));
}
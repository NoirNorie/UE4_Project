// Fill out your copyright notice in the Description page of Project Settings.


#include "PPMenuModeBase.h"

void APPMenuModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartWidgetClass);
}

void APPMenuModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget>NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "TPlayerController.h"

void ATPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//UUserWidget* Widget = CreateWidget<UUserWidget>(this, WidgetAsset);
	//if (Widget)
	//{
	//	Widget->AddToViewport();
	//	Widget->SetVisibility(ESlateVisibility::HitTestInvisible);
	//}
}

void ATPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	//UUserWidget* Widget = CreateWidget<UUserWidget>(this, WidgetAsset);
	//if (Widget)
	//{
	//	Widget->AddToViewport();
	//	Widget->SetVisibility(ESlateVisibility::HitTestInvisible);
	//}

	if (Widget_MainClass != nullptr)
	{
		Widget_Main = CreateWidget<UTPlayerStateWidget>(this, Widget_MainClass);
		if (Widget_Main != nullptr)
		{
			Widget_Main->AddToViewport();
		}
	}

}
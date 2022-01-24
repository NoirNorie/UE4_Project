// Fill out your copyright notice in the Description page of Project Settings.


#include "TPlayerController.h"

void ATPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//if (Widget_MainClass != nullptr)
	//{
	//	Widget_Main = CreateWidget<UTPlayerStateWidget>(this, Widget_MainClass);
	//	if (Widget_Main != nullptr)
	//	{
	//		Widget_Main->AddToViewport();
	//		Widget_Main->SetVisibility(ESlateVisibility::HitTestInvisible);
	//	}
	//}
}

//void ATPlayerController::OnPossess(APawn* aPawn)
//{
//	Super::OnPossess(aPawn);
//
//}

//UTPlayerStateWidget* ATPlayerController::GetPlayerStateWidget() const
//{
//	return Widget_Main; // 위젯 반환
//}
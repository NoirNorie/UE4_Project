// Fill out your copyright notice in the Description page of Project Settings.


#include "GameProgressWidget.h"

void UGameProgressWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GateOpenProgress = Cast<UProgressBar>(GetWidgetFromName(TEXT("GateOpenProgress")));
	ProgressText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ProgressText")));
	progressVar = 0.0f;
}

void UGameProgressWidget::setProgress(float inp)
{
	progressVar = inp;
	GateOpenProgress->SetPercent(progressVar / 100);
}

void UGameProgressWidget::setProgressText()
{
	ProgressText->SetText(FText::FromString("Evacute to Gate"));
}
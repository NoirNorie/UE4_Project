// Fill out your copyright notice in the Description page of Project Settings.


#include "GameProgressWidget.h"

void UGameProgressWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GateOpenProgress = Cast<UProgressBar>(GetWidgetFromName(TEXT("GateOpenProgress")));
	progressVar = 0.0f;
}

void UGameProgressWidget::setProgress(float inp)
{
	progressVar = inp;
	GateOpenProgress->SetPercent(progressVar / 100);
}
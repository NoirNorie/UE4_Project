// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BT_Exit = Cast<UButton>(GetWidgetFromName("BT_Exit"));
	ProgressBox = Cast<UTextBlock>(GetWidgetFromName("ProgressBox"));

	BT_Exit->OnClicked.AddDynamic(this, &UGameOverWidget::ExitButtonCallback);
}

void UGameOverWidget::ExitButtonCallback()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	UGameplayStatics::OpenLevel(GetWorld(), "GameOpen");
}

void UGameOverWidget::SetProgressText(float inputNum)
{
	if (inputNum == 100.0f)
	{
		ProgressBox->SetText(FText::FromString("Survive"));
	}
	else
	{
		ProgressBox->SetText(FText::FromString(FString::SanitizeFloat(inputNum)));
	}
}
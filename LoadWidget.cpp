// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadWidget.h"

void ULoadWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LoadingBox = Cast<UTextBlock>(GetWidgetFromName(TEXT("LoadingBox")));
	Throb = Cast<UCircularThrobber>(GetWidgetFromName(TEXT("Throb")));
}
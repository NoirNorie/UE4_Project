// Fill out your copyright notice in the Description page of Project Settings.


#include "TPlayerWidget.h"

void UTPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UBlueprintGeneratedClass* Widget_PlayerState = LoadObject<UBlueprintGeneratedClass>(
		nullptr,
		TEXT("WidgetBlueprint'/Game/Blueprint/PlayerStateWidget.PlayerStateWidget'")
	);

	Widget_Status = Cast<UClass>(Widget_PlayerState);
}


//UTPlayerWidget::UTPlayerWidget()
//{
//	
//}
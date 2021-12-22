// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UTPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override; // À§Á¬ »ý¼ºÀÚ
	
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* WidgetBox;
	//UPROPERTY(Meta = (BindWidget))
	//	class UCanvasPanel* CanvasPanel;

	UPROPERTY() class UClass* Widget_Status;
public:
	//UTPlayerWidget();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"

#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "MainMenu UI")
		class UButton* BT_Start;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "MainMenu UI")
		class UButton* BT_Exit;
};

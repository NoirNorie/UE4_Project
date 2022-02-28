// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
		void StartButtonCallback();
	UFUNCTION(BlueprintCallable)
		void ExitButtonCallback();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "MainMenu UI")
		class UButton* BT_Start;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "MainMenu UI")
		class UButton* BT_Exit;
};

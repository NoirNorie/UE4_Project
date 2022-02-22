// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable) void ContinueButtonCallback();
	UFUNCTION(BlueprintCallable) void TitleButtonCallback();
	UFUNCTION(BlueprintCallable) void ExitButtonCallback();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Pause UI")
	class UButton* BT_Continue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Pause UI")
	class UButton* BT_Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Pause UI")
	class UButton* BT_Exit;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "Kismet/GameplayStatics.h"

#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void ExitButtonCallback();

	void SetProgressText(float inputNum);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "GameOverUI")
		class UTextBlock* ProgressBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "GameOverUI")
		class UButton* BT_Exit;
};

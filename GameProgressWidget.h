// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "GameProgressWidget.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UGameProgressWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), category = "Game Progress")
		class UProgressBar* GateOpenProgress;

	float progressVar;

public:
	void setProgress(float inp);
};

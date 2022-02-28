// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "ItemInteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UItemInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Info")
		FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Info")
		FString InteractionKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Info")
		float Percent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* ItemNameBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* InteractionKeyBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UProgressBar* InteractionProgressBar;
public:
	virtual void NativeConstruct() override;
	void SetItemName(FString itemName);
	void SetKeyName(FString keyName);
	void SetPercent(float percent);
};

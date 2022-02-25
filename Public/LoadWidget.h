// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CircularThrobber.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EditorLevelLibrary.h"
#include "LoadWidget.generated.h"

/**
 * 
 */
UCLASS()
class PP_API ULoadWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading")
		bool bLoaded;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Loading")
		class UTextBlock* LoadingBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Loading")
		class UCircularThrobber* Throb;
};

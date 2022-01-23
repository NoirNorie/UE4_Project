// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Blueprint/UserWidget.h"
#include "TPlayerStateWidget.h"
#include "TPlayer.h"

#include "TPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PP_API ATPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//	TSubclassOf<class UUserWidget> WidgetAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UTPlayerStateWidget> Widget_MainClass;

	class UTPlayerStateWidget* Widget_Main;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	//	TSubclassOf<class ATPlayer> Player;
protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* aPawn) override;
};

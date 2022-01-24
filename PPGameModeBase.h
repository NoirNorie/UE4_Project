// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

 #include "Blueprint/UserWidget.h"
#include "TPlayerStateWidget.h"

#include "PPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PP_API APPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void StartPlay() override;
	virtual void BeginPlay() override;
	TSubclassOf<UUserWidget> PlayerStateWidgetClass;
	UTPlayerStateWidget* PlayerStateWidget;

public:

	UTPlayerStateWidget* GetPlayerStateWidget() const;


	//UFUNCTION(BlueprintCallable, Category = "UMG_Game")
	//void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	//
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
	//TSubclassOf<UUserWidget> StartingWidgetClass;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
	//UUserWidget* CurrentWidget;
};

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

// 생성자 보조 함수 헤더
#include "UObject/ConstructorHelpers.h"

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

	// virtual void StartPlay() override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UTPlayerStateWidget> StartWidgetClass; // 플레이어의 상태를 출력할 위젯

	UPROPERTY()
	UTPlayerStateWidget* CurrentWidget;

public:
	APPGameModeBase(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void CreateStateWidget(TSubclassOf<UTPlayerStateWidget>NewWidgetClass); 

	UTPlayerStateWidget* GetPlayerStateWidget() const;
};

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

// 위젯 헤더
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "TPlayerWidget.h"

// 생성자 보조함수 헤더
#include "UObject/ConstructorHelpers.h"

#include "PPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PP_API APPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:

	// 위젯 출력용 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = true))
	TSubclassOf<class UTPlayerWidget>Player_StatusWidget;
	UPROPERTY() class UTPlayerWidget* StatusWidget;
};

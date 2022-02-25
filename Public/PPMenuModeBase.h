// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

// 생성자 보조 함수 헤더
#include "UObject/ConstructorHelpers.h"

// 위젯 헤더
#include "Blueprint/UserWidget.h"
#include "MainMenu.h"

#include "PPMenuModeBase.generated.h"

// 게임 시작 메뉴 모드

/**
 * 
 */
UCLASS()
class PP_API APPMenuModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	APPMenuModeBase();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UMainMenu> MainMenuWidgetclass; // 메인 메뉴 위젯
	class UMainMenu* MainMenuWidget;

public:
	
};

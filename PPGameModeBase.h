// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

// 위젯 헤더
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"

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
	// void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass); // 위젯 변경 함수

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void CreatePlayerWidget(TSubclassOf<UUserWidget> NewWidgetClass); // 위젯 생성 함수

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass; // 출력할 위젯
	//
	UPROPERTY() UUserWidget* CurrentWidget; // 출력되고 있던 위젯 변수


};

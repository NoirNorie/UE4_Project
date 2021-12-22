// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

// ���� ���
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "TPlayerWidget.h"

// ������ �����Լ� ���
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
	// void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass); // ���� ���� �Լ�

	//UFUNCTION(BlueprintCallable, Category = "UMG Game")
	//void CreatePlayerWidget(TSubclassOf<UUserWidget> NewWidgetClass); // ���� ���� �Լ�

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	//	TSubclassOf<UUserWidget> StartingWidgetClass; // ����� ����
	////
	//UPROPERTY() UUserWidget* CurrentWidget; // ��µǰ� �ִ� ���� ����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = true))
	TSubclassOf<class UTPlayerWidget>Player_StatusWidget;

	UPROPERTY() class UTPlayerWidget* StatusWidget;


};

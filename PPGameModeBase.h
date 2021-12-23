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

	// ���� ��¿� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = true))
	TSubclassOf<class UTPlayerWidget>Player_StatusWidget;
	UPROPERTY() class UTPlayerWidget* StatusWidget;
};

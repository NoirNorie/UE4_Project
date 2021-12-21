// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

// 엔진 위에 그리기 위한 헤더
#include "Engine/Canvas.h" 

// 위젯 출력을 위한 헤더
#include "Blueprint/UserWidget.h"

#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class PP_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
		UTexture2D* CrosshairTexture;

public:
	virtual void DrawHUD() override;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

// 생성자 보조 함수 헤더
#include "UObject/ConstructorHelpers.h"

//#include "Global.h"
#include "Engine/Canvas.h"

#include "TPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class PP_API ATPlayerHUD : public AHUD
{
	GENERATED_BODY()
public:
	//ATPlayerHUD();
	virtual void DrawHUD() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* CrossHair;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Widget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#include "TPlayerStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UTPlayerStateWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UTPlayerStateWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Player State UI")
	class UClass* Widget_Status;

	//// 텍스트 블록
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), category = "Player State UI")
	class UTextBlock* WeaponNameBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), category = "Player State UI")
	class UTextBlock* CurrentAmmoBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), category = "Player State UI")
	class UTextBlock* RemainAmmoBox;
	
	// 막대 바
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), category = "Player State UI")
	class UProgressBar* HPBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), category = "Player State UI")
	class UProgressBar* HungryBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), category = "Player State UI")
	class UProgressBar* ThirstBar;

public:
	// 사용할 변수들
	FName UI_WeaponName;
	FName UI_CurrentAmmo;
	FName UI_RemainAmmo;

	float UI_HP;
	float UI_HungryBar;
	float UI_ThirstBar;

	void SetWeaponName(FName WName);
	void SetCurrentAmmo(int32 ammo);
	void SetRemainAmmo(int32 ammo);

	void SetCurrentHP(float hp);
	void SetCurrentHungry(float hungry);
	void SetCurrentThirst(float thirst);

};

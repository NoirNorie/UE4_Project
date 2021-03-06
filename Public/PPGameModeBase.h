// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

// 생성자 보조 함수 헤더
#include "UObject/ConstructorHelpers.h"

#include "Kismet/GameplayStatics.h"

#include "Blueprint/UserWidget.h"
#include "TPlayerStateWidget.h"
#include "GameProgressWidget.h"
#include "InventoryBase.h"
#include "GameOverWidget.h"
#include "PauseWidget.h"

#include "PPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PP_API APPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	// virtual void StartPlay() override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UTPlayerStateWidget> StartWidgetClass;  // 플레이어의 상태를 출력할 위젯
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UInventoryBase> InventoryClass;			// 인벤토리를 띄울 위젯
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UGameProgressWidget> GameProgressClass; // 게임 진행 상황을 띄울 위젯
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UGameOverWidget> GameOverWidgetClass;	// 게임 종료 상황을 띄울 위젯
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UPauseWidget> PauseWidgetClass;			// 게임 정지 후 메뉴를 띄울 위젯

	UPROPERTY() UTPlayerStateWidget* CurrentWidget;
	UPROPERTY() UInventoryBase* PlayerInventory;
	UPROPERTY() UGameProgressWidget* ProgressWidget;
	UPROPERTY() UGameOverWidget* GameOverWidget;
	UPROPERTY() UPauseWidget* PauseWidget;

public:
	APPGameModeBase(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void CreateStateWidget(TSubclassOf<UTPlayerStateWidget>NewWidgetClass);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void CreateInventory(TSubclassOf<UInventoryBase>NewInventoryClass);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void CreateProgressWidget(TSubclassOf<UGameProgressWidget>NewProgressClass);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void CreateGameOverWidget(TSubclassOf<UGameOverWidget>NewGameOverWidgetClass);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void CreatePauseWidget(TSubclassOf<UPauseWidget>NewPauseWidgetClass);

	UTPlayerStateWidget* GetPlayerStateWidget() const;		// 플레이어 상태창 반환
	UInventoryBase* GetInventoryWidget() const;				// 플레이어 인벤토리 반환
	UGameProgressWidget* GetGameProgressWidget() const;		// 게임 진행 상황 위젯 반환
	UGameOverWidget* GetGameOverWidget() const;				// 게임 오버 위젯 반환
	UPauseWidget* GetPauseWidget() const;					// 정지 메뉴 위젯 반환

	void GameOverWidgetOnline(float GateOpenProgress) const;						// 게임 오버 위젯을 출력하기 위한 함수


};


/*
	언리얼 게임 플레이 파이프라인에 따라서
	- StartPlay()로 위젯을 초기화 할 경우 캐릭터에서 위젯을 받아올 때 위젯을 제대로 받아내지 못한다
	- 캐릭터의 BeginPlay()보다 게임모드의 StartPlay()가 느리게 실행된다
	- 따라서 GetPlayerStateWidget()으로 현재 위젯을 넘겨줘도 의미가 없게 된다.
	- BeginPlay()에서 위젯을 초기화 할 경우 캐릭터의 BeginPlay()보다 먼저 실행되어 제대로 위젯이 초기화된다
*/
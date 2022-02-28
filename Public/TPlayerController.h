// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

// 생성자 보조 함수 헤더
#include "UObject/ConstructorHelpers.h"

#include "Kismet/GameplayStatics.h"

#include "Blueprint/UserWidget.h"
#include "TPlayerStateWidget.h"
#include "GameProgressWidget.h"
#include "InventoryBase.h"
#include "GameOverWidget.h"
#include "PauseWidget.h"


#include "TPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PP_API ATPlayerController : public APlayerController
{
	GENERATED_BODY()
public:





public:
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

};

// Copyright Epic Games, Inc. All Rights Reserved.


#include "PPGameModeBase.h"

APPGameModeBase::APPGameModeBase(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	//// 위젯 읽어오기
	//static ConstructorHelpers::FClassFinder<UTPlayerStateWidget> PlayerStateWidgetAsset(
	//	TEXT("/Game/Blueprint/Widget/PlayerWidget")
	//);

	//if (PlayerStateWidgetAsset.Succeeded())
	//{
	//	PlayerStateWidgetClass = PlayerStateWidgetAsset.Class;
	//}
}

//void APPGameModeBase::StartPlay()
//{
//	Super::StartPlay();
//
//	if (GEngine)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Game Start"));
//	}
//}

void APPGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Begin Start"));
	//}
	CreateStateWidget(StartWidgetClass);
	CreateProgressWidget(GameProgressClass);
	CreateInventory(InventoryClass);
	CreatePauseWidget(PauseWidgetClass);
	CreateGameOverWidget(GameOverWidgetClass);

}
// 플레이어 상태창 등록
void APPGameModeBase::CreateStateWidget(TSubclassOf<UTPlayerStateWidget>NewWidgetClass)
{
	if (CurrentWidget != nullptr) // 띄워진 위젯이 있다면
	{

		CurrentWidget->RemoveFromViewport(); // 위젯을 지운다.
		CurrentWidget = nullptr;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("RemoveWidget")));
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UTPlayerStateWidget>(GetWorld(), NewWidgetClass); // 위젯은 BP에서 직접 등록한다(BP의 UMG Game 항목에 있음)
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("LocateWidget")));
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport(); // 위젯을 띄운다.
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AddWidget")));
		}
	}

}
// 플레이어 인벤토리 등록
void APPGameModeBase::CreateInventory(TSubclassOf<UInventoryBase>NewInventoryClass)
{
	if (PlayerInventory != nullptr) // 등록된 무엇인가 존재한다면
	{
		PlayerInventory->RemoveFromViewport();
		PlayerInventory = nullptr;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("RemoveInventory")));
		// 내용을 비워놓는다.
	}
	if (NewInventoryClass != nullptr) // 인벤토리로 등록해놓은 클래스가 유효한지 확인한다.
	{
		PlayerInventory = CreateWidget<UInventoryBase>(GetWorld(), NewInventoryClass);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("LocateInventory")));
		if (PlayerInventory != nullptr)
		{
			PlayerInventory->AddToViewport();
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AddInventory")));
		}

		PlayerInventory->SetVisibility(ESlateVisibility::Collapsed); // 일단 안보이게 한다.
	}
}
// 게임 진행도 위젯 등록
void APPGameModeBase::CreateProgressWidget(TSubclassOf<UGameProgressWidget>NewProgressClass)
{
	if (ProgressWidget != nullptr)
	{
		ProgressWidget->RemoveFromViewport();
		ProgressWidget = nullptr;
	}
	if (NewProgressClass != nullptr)
	{
		ProgressWidget = CreateWidget<UGameProgressWidget>(GetWorld(), NewProgressClass);
		if (ProgressWidget != nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("FindProgressWidget")));
			ProgressWidget->AddToViewport();
			ProgressWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
// 게임 오버 위젯 등록
void APPGameModeBase::CreateGameOverWidget(TSubclassOf<UGameOverWidget>NewGameOverWidgetClass)
{
	if (GameOverWidget != nullptr)
	{
		GameOverWidget->RemoveFromParent();
		GameOverWidget = nullptr;
	}
	if(NewGameOverWidgetClass != nullptr)
	{
		GameOverWidget = CreateWidget<UGameOverWidget>(GetWorld(), NewGameOverWidgetClass);
		if (GameOverWidget != nullptr)
		{
			GameOverWidget->AddToViewport();
			GameOverWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}
// 정지 메뉴 위젯 등록
void APPGameModeBase::CreatePauseWidget(TSubclassOf<UPauseWidget>NewPauseWidgetClass)
{
	if (PauseWidget != nullptr)
	{
		PauseWidget->RemoveFromParent();
		PauseWidget = nullptr;
	}
	if (NewPauseWidgetClass != nullptr)
	{
		PauseWidget = CreateWidget<UPauseWidget>(GetWorld(), NewPauseWidgetClass);
		if (PauseWidget != nullptr)
		{
			PauseWidget->AddToViewport();
			PauseWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

// 띄워진 위젯을 반환하는 함수들
UTPlayerStateWidget* APPGameModeBase::GetPlayerStateWidget() const
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("return Widget")));
	return CurrentWidget;
}

UInventoryBase* APPGameModeBase::GetInventoryWidget() const
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("return Inventory")));
	return PlayerInventory;
}

UGameProgressWidget* APPGameModeBase::GetGameProgressWidget() const
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("return Progress Widget")));
	return ProgressWidget;
}

UGameOverWidget* APPGameModeBase::GetGameOverWidget() const
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("return GameOver Widget")));
	return GameOverWidget;
}

UPauseWidget* APPGameModeBase::GetPauseWidget() const
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("return Pause Widget")));
	return PauseWidget;
}

void APPGameModeBase::GameOverWidgetOnline(float GateOpenProgress) const
{
	if (GameOverWidget != nullptr)
	{


		GameOverWidget->SetProgressText(GateOpenProgress);
		GameOverWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
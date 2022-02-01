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
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Begin Start"));
	}
	CreateStateWidget(StartWidgetClass);
	CreateInventory(InventoryClass);
}
// 플레이어 상태창 등록
void APPGameModeBase::CreateStateWidget(TSubclassOf<UTPlayerStateWidget>NewWidgetClass)
{
	if (CurrentWidget != nullptr) // 띄워진 위젯이 있다면
	{

		CurrentWidget->RemoveFromViewport(); // 위젯을 지운다.
		CurrentWidget = nullptr;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("RemoveWidget")));
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UTPlayerStateWidget>(GetWorld(), NewWidgetClass); // 위젯은 BP에서 직접 등록한다(BP의 UMG Game 항목에 있음)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("LocateWidget")));
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport(); // 위젯을 띄운다.
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AddWidget")));
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
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("RemoveInventory")));
		// 내용을 비워놓는다.
	}
	if (NewInventoryClass != nullptr) // 인벤토리로 등록해놓은 클래스가 유효한지 확인한다.
	{
		PlayerInventory = CreateWidget<UInventoryBase>(GetWorld(), NewInventoryClass);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("LocateInventory")));
		if (PlayerInventory != nullptr)
		{
			PlayerInventory->AddToViewport();
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AddInventory")));
		}

		PlayerInventory->SetVisibility(ESlateVisibility::Collapsed); // 일단 안보이게 한다.
	}
}


// 띄워진 위젯을 반환하는 함수
UTPlayerStateWidget* APPGameModeBase::GetPlayerStateWidget() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("return Widget")));
	return CurrentWidget;
}

UInventoryBase* APPGameModeBase::GetInventoryWidget() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("return Inventory")));
	return PlayerInventory;
}
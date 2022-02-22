// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BT_Continue = Cast<UButton>(GetWidgetFromName(TEXT("BT_Continue")));
	BT_Title = Cast<UButton>(GetWidgetFromName(TEXT("BT_Title")));
	BT_Exit = Cast<UButton>(GetWidgetFromName(TEXT("BT_Exit")));

	BT_Continue->OnClicked.AddDynamic(this, &UPauseWidget::ContinueButtonCallback);
	BT_Title->OnClicked.AddDynamic(this, &UPauseWidget::TitleButtonCallback);
	BT_Exit->OnClicked.AddDynamic(this, &UPauseWidget::ExitButtonCallback);
}

void UPauseWidget::ContinueButtonCallback()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	this->SetVisibility(ESlateVisibility::Collapsed); // 안보이게 만든다.
}

void UPauseWidget::TitleButtonCallback()
{
	UGameplayStatics::OpenLevel(GetWorld(), "GameOpen"); // 메인 메뉴로
}

void UPauseWidget::ExitButtonCallback()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true); // 게임 종료 버튼
}
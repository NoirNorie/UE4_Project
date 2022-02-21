// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	BT_Start = Cast<UButton>(GetWidgetFromName(TEXT("BT_Start")));
	BT_Exit = Cast<UButton>(GetWidgetFromName(TEXT("BT_Exit")));

	BT_Start->OnClicked.AddDynamic(this, &UMainMenu::StartButtonCallback);
	BT_Exit->OnClicked.AddDynamic(this, &UMainMenu::ExitButtonCallback);

}

void UMainMenu::StartButtonCallback()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Basic");
	// 레퍼런스 경로가 아닌 맵의 이름을 적어야 한다

}

void UMainMenu::ExitButtonCallback()
{
	// 게임을 종료한다.
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true);
}
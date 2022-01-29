// Fill out your copyright notice in the Description page of Project Settings.


#include "PPMenuModeBase.h"

APPMenuModeBase::APPMenuModeBase()
{
	//static ConstructorHelpers::FClassFinder<UMainMenu>MainMenuClass(TEXT(
	//	"WidgetBlueprint'/Game/Blueprint/Widget/MainMenu.MainMenu'")
	//);

	//if (MainMenuClass.Succeeded()) // 위젯을 해당 경로로부터 가져오는데 성공했다면
	//{
	//	MainMenuWidgetclass = MainMenuClass.Class;
	//}

	// 위젯은 에디터에서 할당한다.
}

void APPMenuModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidgetclass)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuWidgetclass);

		if(MainMenuWidget != nullptr) // 위젯이 타당하다면
		{
			MainMenuWidget->AddToViewport(); // 뷰포트에 넣는다.
		}
	}
}
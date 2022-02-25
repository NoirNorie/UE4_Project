// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuController.h"

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeUIOnly()); // UI 입력만 받는다.
}
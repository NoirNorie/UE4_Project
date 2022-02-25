// Fill out your copyright notice in the Description page of Project Settings.


#include "TPlayerController.h"

void ATPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// SetInputMode(FInputModeGameAndUI());
	SetInputMode(FInputModeGameOnly()); // 게임모드로 변환한다.
}
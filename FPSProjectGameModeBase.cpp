// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPSProjectGameModeBase.h"

void AFPSProjectGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	check(GEngine != nullptr);

	// 디버그 메시지를 5초간 출력하도록 한다
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
	// 키 값 인자 -1 = 메시지가 업데이트나 리프레쉬되는 것을 막아준다.
	// 여기까지 했지만 언리얼 에디터 상에서 실행시켜도 아직 출력되지 않는다



}
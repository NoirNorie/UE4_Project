// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPSProjectGameModeBase.h"

void AFPSProjectGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	check(GEngine != nullptr);

	// ����� �޽����� 5�ʰ� ����ϵ��� �Ѵ�
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
	// Ű �� ���� -1 = �޽����� ������Ʈ�� ���������Ǵ� ���� �����ش�.
	// ������� ������ �𸮾� ������ �󿡼� ������ѵ� ���� ��µ��� �ʴ´�



}
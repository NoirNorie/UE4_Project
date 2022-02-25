// Fill out your copyright notice in the Description page of Project Settings.


#include "RootingBoxAmmo.h"

ARootingBoxAmmo::ARootingBoxAmmo()
{
	Box_Name = "Ammo Box";
}

void ARootingBoxAmmo::DropItem()
{
	int32 RandomNumb = FMath::RandRange(1, 10);
	if (RandomNumb >= 5 && RandomNumb <= 7) // 총알만 떨어뜨린다.
	{
		UWorld* world = GetWorld();
		if (world != nullptr)
		{
			// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("current Random Number %d"), RandomNumb));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			FRotator rotator;
			FVector SpawnLocation = GetActorLocation();
			world->SpawnActor<AActor>(*(ItemBPMap.Find(RandomNumb)), SpawnLocation, rotator, SpawnParams);
		}
	}
}
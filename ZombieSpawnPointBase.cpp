// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieSpawnPointBase.h"

// Sets default values
AZombieSpawnPointBase::AZombieSpawnPointBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // 필요 없으므로 틱 함수를 잠근다.
	Isnight = false;
	SpawnZombie = nullptr;
	ZombieCounter = 0;
}

// Called when the game starts or when spawned
void AZombieSpawnPointBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombieSpawnPointBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieSpawnPointBase::ZombieSpawn()
{
	if (Isnight && ZombieCounter <= 10)
	{
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnZombie = GetWorld()->SpawnActor<AAZombie>(Zombieclass, GetActorLocation(), GetActorRotation(), params);
		ZombieCounter++;
	}
}
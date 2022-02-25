// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AZombie.h"
#include "ZombieSpawnPointBase.generated.h"

UCLASS()
class PP_API AZombieSpawnPointBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZombieSpawnPointBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowprivateAccess = "true"), category = "Spawn")
	TSubclassOf<class AAZombie> Zombieclass;



	UFUNCTION(BlueprintCallable) // 해가 지면 좀비를 생성하기 위해 함수 실행은 블루프린트에서 한다.
		void ZombieSpawn();

	class AAZombie* SpawnZombie;

	int32 ZombieCounter;

public:	
	// Called every frame
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"), category = "Spawn")
		float SpawnTime;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowprivateAccess = "true"), category = "Spawn")
		bool Isnight;

};

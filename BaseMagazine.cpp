// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMagazine.h"

// Sets default values
ABaseMagazine::ABaseMagazine()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	Mag_Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WCapsule")); // ĸ�� ������Ʈ ����
	Mag_Capsule->SetupAttachment(RootComponent); // ��Ʈ ������Ʈ�� ����

	Mag_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shape")); // ����ƽ �޽� ������Ʈ ����
	Mag_Mesh->SetupAttachment(Mag_Capsule); // ĸ�� ������Ʈ�� ����
}

// Called when the game starts or when spawned
void ABaseMagazine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseMagazine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


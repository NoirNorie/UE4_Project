// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	W_Contact = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WCapsule")); // Ä¸½¶ ÄÄÆ÷³ÍÆ® »ý¼º
	W_Contact->SetupAttachment(RootComponent); // ·çÆ® ÄÄÆ÷³ÍÆ®¿¡ ºÎÂøÇÑ´Ù.

	SK_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shape")); // ½ºÄÌ·¹Å» ¸Þ½Ã ÄÄÆ÷³ÍÆ® »ý¼º
	SK_Mesh->SetupAttachment(W_Contact); // Ä¸½¶ ÄÄÆ÷³ÍÆ®¿¡ ºÎÂøÇÑ´Ù.
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
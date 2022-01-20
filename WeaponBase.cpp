// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	W_Contact = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WCapsule"));
	W_Contact->SetupAttachment(RootComponent);
	SK_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shape"));
	SK_Mesh->SetupAttachment(W_Contact);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	W_Contact->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnBeginOverlap);
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->ActorHasTag(TEXT("Player"))) // 플레이어와만 상호작용을 하도록 만든다
		{
			bool IsImplemented = OtherActor->GetClass()->ImplementsInterface(UTPlayerInterface::StaticClass());
			if (IsImplemented)
			{
				ITPlayerInterface* EQWeaponInterface = Cast<ITPlayerInterface>(OtherActor);
				if (EQWeaponInterface)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Interface Active")));
					EQWeaponInterface->Execute_EquipWeaponItem(OtherActor, Weapon_Name, W_Ammo, W_Damage, W_FireRate, W_IDX);
				}
				Destroy(); // 아이템을 획득할 경우 제거
			}
		}
	}
}
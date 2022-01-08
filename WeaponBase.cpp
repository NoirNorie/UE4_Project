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
	W_Contact->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnBeginOverlap);
	DrawDebugSphere(GetWorld(), GetActorLocation(), W_Contact->GetScaledCapsuleRadius(), 20, FColor::Red, true);
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->ActorHasTag(TEXT("Player")))
		{
			bool IsImplemented = OtherActor->GetClass()->ImplementsInterface(UTPlayerInterface::StaticClass());
			if (IsImplemented)
			{
				ITPlayerInterface* EQWeaponInterface = Cast<ITPlayerInterface>(OtherActor);
				if (EQWeaponInterface)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Interface Active")));
					EQWeaponInterface->Execute_EquipWeaponItem(OtherActor, Weapon_Name, W_Ammo, W_Damage, W_FireRate); // ÀÎÅÍÆäÀÌ½º·Î °ª Àü´Þ
				}			
				Destroy();
			}		
		}
	}
}

//void AWeaponBase::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
//	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
//	bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (OtherActor && (OtherActor != this) && OtherComp)
//	{
//		ITPlayerInterface* WeaponInterface = Cast<ITPlayerInterface>(OtherActor);
//		if (WeaponInterface)
//		{
//			WeaponInterface->Execute_Equip_WeaponItem(OtherActor, Weapon_Name, W_Ammo, W_Damage, W_FireRate);
//		}
//		Destroy();
//
//	}
//}
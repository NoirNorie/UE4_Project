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

	// 위젯이 표시될 곳을 만들어 놓는다.
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));

	bOverlapped = false;
	progressVar = 0.0f;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (ItemInterClass != nullptr)
	{
		ItemWidget = CreateWidget<UItemInteractionWidget>(GetWorld(), ItemInterClass);
		if (ItemWidget != nullptr)
		{
			ItemWidget->AddToViewport(); // 위젯을 띄운다.
			ItemWidget->SetVisibility(ESlateVisibility::Collapsed); // 안보이게 만든다.
		}
	}

	W_Contact->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnBeginOverlap);

}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bOverlapped == true)
	{
		progressVar += 1.0f;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Active %f"), progressVar));

		if (progressVar >= 100.0f)
		{
			Destroy();
		}
	}
	

}

void AWeaponBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->ActorHasTag(TEXT("Player"))) // 플레이어와만 상호작용을 하도록 만든다
		{
			bOverlapped = true; // 충돌 상태를 true로 바꾼다.

			bool IsImplemented = OtherActor->GetClass()->ImplementsInterface(UTPlayerInterface::StaticClass());
			if (IsImplemented)
			{
				ITPlayerInterface* EQWeaponInterface = Cast<ITPlayerInterface>(OtherActor);
				if (EQWeaponInterface)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Interface Active")));
					EQWeaponInterface->Execute_EquipWeaponItem(OtherActor, Weapon_Name, W_Ammo, W_Damage, W_FireRate, W_IDX);
				}
				// Destroy(); // 아이템을 획득할 경우 제거
			}

			// ItemWidget->SetVisibility(ESlateVisibility::Visible); // 보이게 한다.
			//if (progressVar >= 100.0f)
			//{
			//	
			//}
		}
	}
}
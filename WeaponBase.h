// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "ItemInteractionWidget.h"

#include "TPlayer.h"
#include "TPlayerInterface.h"

#include "WeaponBase.generated.h"

UCLASS()
class PP_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Casule", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* W_Contact;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* SK_Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractionWidget", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* Inter_Widget;

	UItemInteractionWidget* DisplayedWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	class ATPlayer* InfoPlayer;

	// void CreateInteractionWidget();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Info: Name")
	FName Weapon_Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Info: Ammo")
	int32 W_Ammo;
	UPROPERTY(VIsibleAnywhere, BlueprintReadOnly, Category = "Weapon Info: WeaponDamage")
	float W_Damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Info: FireRate")
	float W_FireRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Info: WeaponIndex")
	int32 W_IDX;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Progress Variables")
	float progressVar;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION() void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION() void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION() void GiveItem();

	UFUNCTION() void CallDeleFunc_LootingStart();
	UFUNCTION() void CallDeleFunc_LootingCancle();


	bool bOverlapped;
	bool bLooting;
	AActor* TransferActor;
};
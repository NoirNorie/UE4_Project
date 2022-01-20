// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Casule, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* W_Contact;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* SK_Mesh;

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


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
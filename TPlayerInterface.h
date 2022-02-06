// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TPlayerInterface.generated.h"

// 플레이어 인터페이스 클래스

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PP_API ITPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 무기 장착 확인용 인터페이스 함수
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CheckWeapon")
	void EquipWeaponItem(FName weapon_Name, int32 weaponAmmo, float weaponDamage, float weaponFireRate, int32 weaponType);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GetAmmo")
	void GetAmmoItem(FName Ammo_Name, int32 Ammo_Type);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GetFood")
	void GetFoodItem(FName Food_Name, float fHungry, float fThirsty);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TPlayerInterface.generated.h"

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

	// Add interface functions to this class. This is the class that will be inherited to implementthis interface.
	
	// 인터페이스 함수
public:
	// 무기 장착 여부 확인 인터페이스 함수
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CheckWeapon")
	//void Equip_WeaponItem();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CheckWeapon")
	void Equip_WeaponItem(FName weaponName, int32 weaponAmmo); // 인터페이스는 구현이 불가능함

	// 탄창 획득 인터페이스 함수
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GetMagazine")
	void Get_Magazine(FName MagName, int32 MagType);


	// 조준 여부 확인 인터페이스 함수
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AimState")
	void Player_Aiming();
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Rifle.h"

AW_Rifle::AW_Rifle()
{
	// 총알 초기화
	Weapon_Name = "AR-15";
	W_Ammo = 30;
	W_Damage = 25.0f;
	W_FireRate = 0.1f;
	W_IDX = 0;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "TAnimInstance.h"

UTAnimInstance::UTAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
}

void UTAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 폰을 받아온다
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}

	// 캐릭터 타입으로 폰을 형변환
	ATPlayer* Character = Cast<ATPlayer>(Pawn);
	if (Character) // 읽어오는데 성공했다면
	{	
		// 공중에 떠있는지 판정한다	
		IsInAir = Character->GetMovementComponent()->IsFalling(); 
		// 이동 속도를 받아온다
		CurrentWalkSpeed = Character->GetMovementComponent()->GetMaxSpeed(); 		
		// 무기 장착 여부를 확인한다
		WeaponState = Character->GetWeaponCheck();
		// 조준 상태 확인
		Aiming = Character->GetAimCheck();
		// 바라보고 있는 방향을 확인한다.
		Direction = CalculateDirection(Character->GetVelocity(), Character->GetControlRotation());
		aim_Pitch = Character->GetBaseAimRotation().Pitch;
		aim_Yaw = Character->GetBaseAimRotation().Yaw;
	}
}

// 사격 함수
void UTAnimInstance::PlayFire()
{
	IsFire = true; // 사격 시작
}

// 사격 모션이 종료된 것을 확인하는 노티파이 함수
void UTAnimInstance::AnimNotify_FireEnd()
{
	// 폰을 받아온다
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
	// 캐릭터 타입으로 폰을 형변환
	ATPlayer* Character = Cast<ATPlayer>(Pawn);
	if (Character)
	{
		Character->player_ammo--; // 탄약을 1회 줄인다.
	}
	IsFire = false; // 사격 종료
}

// 재장전 함수
void UTAnimInstance::PlayReload()
{
	IsReload = true; // 재장전 시작
}

// 재장전 종료를 알릴 노티파이 함수
void UTAnimInstance::AnimNotify_ReloadEnd()
{
	// 폰을 받아온다
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
	// 캐릭터 타입으로 폰을 형변환
	ATPlayer* Character = Cast<ATPlayer>(Pawn);
	if (Character)
	{
		Character->player_ammo = 30; // 일단 AR 탄창으로 고정한다
		Character->player_mag--; // 탄창을 1개 줄인다.
	}
	IsReload = false; // 재장전 종료
}
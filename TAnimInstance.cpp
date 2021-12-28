// Fill out your copyright notice in the Description page of Project Settings.


#include "TAnimInstance.h"

UTAnimInstance::UTAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
}

void UTAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// ���� �޾ƿ´�
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}

	// ĳ���� Ÿ������ ���� ����ȯ
	ATPlayer* Character = Cast<ATPlayer>(Pawn);
	if (Character) // �о���µ� �����ߴٸ�
	{	
		// ���߿� ���ִ��� �����Ѵ�	
		IsInAir = Character->GetMovementComponent()->IsFalling(); 
		// �̵� �ӵ��� �޾ƿ´�
		CurrentWalkSpeed = Character->GetMovementComponent()->GetMaxSpeed(); 		
		// ���� ���� ���θ� Ȯ���Ѵ�
		WeaponState = Character->GetWeaponCheck();
		// ���� ���� Ȯ��
		Aiming = Character->GetAimCheck();
		// �ٶ󺸰� �ִ� ������ Ȯ���Ѵ�.
		Direction = CalculateDirection(Character->GetVelocity(), Character->GetControlRotation());
		aim_Pitch = Character->GetBaseAimRotation().Pitch;
		aim_Yaw = Character->GetBaseAimRotation().Yaw;
	}
}

// ��� �Լ�
void UTAnimInstance::PlayFire()
{
	IsFire = true; // ��� ����
}

// ��� ����� ����� ���� Ȯ���ϴ� ��Ƽ���� �Լ�
void UTAnimInstance::AnimNotify_FireEnd()
{
	// ���� �޾ƿ´�
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
	// ĳ���� Ÿ������ ���� ����ȯ
	ATPlayer* Character = Cast<ATPlayer>(Pawn);
	if (Character)
	{
		Character->player_ammo--; // ź���� 1ȸ ���δ�.
	}
	IsFire = false; // ��� ����
}

// ������ �Լ�
void UTAnimInstance::PlayReload()
{
	IsReload = true; // ������ ����
}

// ������ ���Ḧ �˸� ��Ƽ���� �Լ�
void UTAnimInstance::AnimNotify_ReloadEnd()
{
	// ���� �޾ƿ´�
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
	// ĳ���� Ÿ������ ���� ����ȯ
	ATPlayer* Character = Cast<ATPlayer>(Pawn);
	if (Character)
	{
		Character->player_ammo = 30; // �ϴ� AR źâ���� �����Ѵ�
		Character->player_mag--; // źâ�� 1�� ���δ�.
	}
	IsReload = false; // ������ ����
}
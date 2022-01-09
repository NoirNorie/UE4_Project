// Fill out your copyright notice in the Description page of Project Settings.


#include "TAnimInstance.h"

UTAnimInstance::UTAnimInstance()
{
	CurrentPawnSpeed = 0.0f;

	static ConstructorHelpers::FObjectFinder<USoundCue>RifleShot(TEXT("SoundCue'/Game/Blueprint/WeaponSound/Rifle2_Cue.Rifle2_Cue'"));
	if (RifleShot.Succeeded())
	{
		ShotCue = RifleShot.Object;
	}
	ShotCueComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ShotSoundCue"));
	ShotCueComponent->SetSound(ShotCue);
	
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
	//static ConstructorHelpers::FObjectFinder<USoundCue>RifleShot(TEXT("SoundCue'/Game/Blueprint/WeaponSound/Rifle2_Cue.Rifle2_Cue'"));
	//if (RifleShot.Succeeded())
	//{
	//	ShotCue = RifleShot.Object;
	//}
	//ShotCueComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ShotSoundCue"));
	//ShotCueComponent->SetSound(ShotCue);
	ShotCueComponent->SetIntParameter("soundSelect", shotIDX);
}

// ��� �Լ�
void UTAnimInstance::PlayFire()
{
	IsFire = true; // ��� ����
}
void UTAnimInstance::AnimNotify_FireStart() //
{
	//ShotCueComponent->SetIntParameter("soundSelect", soundIDX);
	//shotIDX = soundIDX;
	//ShotCueComponent->SetIntParameter("soundSelect", shotIDX);
	ShotCueComponent->Play();
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
		
		if (Character->WeaponName == "AR-15")
		{
			Character->player_ammo = 30;
		}
		else if (Character->WeaponName == "AK-47")
		{
			Character->player_ammo = 25;
		}
		else if (Character->WeaponName == "KA-Val")
		{
			Character->player_ammo = 11;
		}

		Character->player_mag--; // źâ�� 1�� ���δ�.
	}
	IsReload = false; // ������ ����
}
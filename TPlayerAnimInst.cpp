// Fill out your copyright notice in the Description page of Project Settings.


#include "TPlayerAnimInst.h"
#include "TPlayer.h"

UTPlayerAnimInst::UTPlayerAnimInst()
{
	CurrentPawnSpeed = 0.0f;

	static ConstructorHelpers::FObjectFinder<USoundCue>RifleShot(TEXT("SoundCue'/Game/Blueprint/WeaponSound/Rifle2_Cue.Rifle2_Cue'"));
	if (RifleShot.Succeeded())
	{
		ShotCue = RifleShot.Object;
		ShotCueComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ShotSoundCue"));
		ShotCueComponent->SetSound(ShotCue);
	}

	WeaponState = false;

}

void UTPlayerAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 이동 속도를 받아온다.
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}

	ATPlayer* Character = Cast<ATPlayer>(Pawn);
	if (Character)
	{
		IsInAir = Character->GetMovementComponent()->IsFalling();
		CurrentWalkSpeed = Character->GetMovementComponent()->GetMaxSpeed();
		WeaponState = Character->GetWeaponCheck();
		Aiming = Character->GetAimCheck();
		Direction = CalculateDirection(Character->GetVelocity(), Character->GetControlRotation());
		aim_Pitch = Character->GetBaseAimRotation().Pitch;
		aim_Yaw = Character->GetBaseAimRotation().Yaw;
	}

	if (ShotCueComponent)
	{
		ShotCueComponent->SetIntParameter("soundSelect", ShotIDX);
	}
}

void UTPlayerAnimInst::PlayFire()
{
	IsFire = true;
}
void UTPlayerAnimInst::AnimNotify_FireStart()
{
	ShotCueComponent->Play();
}
void UTPlayerAnimInst::AnimNotify_FireEnd()
{
	//auto Pawn = TryGetPawnOwner();
	//if (::IsValid(Pawn))
	//{
	//	CurrentPawnSpeed = Pawn->GetVelocity().Size();
	//}
	//ATPlayer* Character = Cast<ATPlayer>(Pawn);
	//if (Character)
	//{
	//	Character->(player_ammo); // 총알을 감소시킨다.
	//}
	IsFire = false;
}

void UTPlayerAnimInst::PlayReload()
{
	IsReload = true;
}
void UTPlayerAnimInst::AnimNotify_ReloadEnd()
{
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
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

		// Character->player_mag--;
		Character->ReloadEnd();
	}
	IsReload = false;
}
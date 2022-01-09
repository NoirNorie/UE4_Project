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
	//static ConstructorHelpers::FObjectFinder<USoundCue>RifleShot(TEXT("SoundCue'/Game/Blueprint/WeaponSound/Rifle2_Cue.Rifle2_Cue'"));
	//if (RifleShot.Succeeded())
	//{
	//	ShotCue = RifleShot.Object;
	//}
	//ShotCueComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ShotSoundCue"));
	//ShotCueComponent->SetSound(ShotCue);
	ShotCueComponent->SetIntParameter("soundSelect", shotIDX);
}

// 사격 함수
void UTAnimInstance::PlayFire()
{
	IsFire = true; // 사격 시작
}
void UTAnimInstance::AnimNotify_FireStart() //
{
	//ShotCueComponent->SetIntParameter("soundSelect", soundIDX);
	//shotIDX = soundIDX;
	//ShotCueComponent->SetIntParameter("soundSelect", shotIDX);
	ShotCueComponent->Play();
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

		Character->player_mag--; // 탄창을 1개 줄인다.
	}
	IsReload = false; // 재장전 종료
}
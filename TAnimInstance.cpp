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
		WeaponState = Character->GetWeaponCheck();
		Aiming = Character->GetAimCheck();
	}

}
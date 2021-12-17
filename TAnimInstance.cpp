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
		WeaponState = Character->GetWeaponCheck();
		Aiming = Character->GetAimCheck();
	}

}
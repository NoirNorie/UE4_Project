// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAnim.h"

UZombieAnim::UZombieAnim()
{
	currentPawnSpeed = 0.0f;
	currentWalkSpeed = 0.0f;
	IsAttacking = false;
	IsDead = false;
	DetectTarget = false;
}

void UZombieAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		currentPawnSpeed = Pawn->GetVelocity().Size();
	}

	AAZombie* Character = Cast<AAZombie>(Pawn);
	if (Character)
	{
		currentWalkSpeed = Character->GetMovementComponent()->GetMaxSpeed();
	}
}

void UZombieAnim::Detect()
{
	DetectTarget = true;
}
void UZombieAnim::Attack()
{
	IsAttacking = true;
}
void UZombieAnim::AnimNotify_AttackEnd()
{
	IsAttacking = false;
}
void UZombieAnim::AnimNotify_DetectEnd()
{
	DetectTarget = false;
}
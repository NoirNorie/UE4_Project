// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// ī�޶� ���� ���
#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"

// ��Ʈ�� ���� ���
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// ������ �� ����� �Լ��� ����ִ� ���
#include "UObject/ConstructorHelpers.h"

// ���� ���� ���
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

#include "FPSProjectile.h"

// �� ����� �ݵ�� �Ʒ��� �־�� �Ѵ�
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles input for moving forward and backward.
	UFUNCTION()
		void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
		void MoveRight(float Value);

	// Sets jump flag when key is pressed.
	UFUNCTION()
		void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
		void StopJump();

	//// Function that handles firing projectiles.
	//// ����ü �߻縦 �ٷ� �Լ� ����
	//UFUNCTION()
	//	void Fire();

	// ���� ������ PvP �� �ƴϹǷ� ��Ʈ��ĵ�� ������ ��� ü�踦 �����
	FTimerHandle timer;
	UPROPERTY() bool isFiring;
	UFUNCTION()
		void StartFire();
	UFUNCTION()
		void StopFire();
	void Fire();

	// �޸��� �Լ� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedMultiplier;

	UFUNCTION() 
		void StartRun();
	UFUNCTION() 
		void StopRun();

	// ����
	UAudioComponent* AudioComponent;
	USoundBase* Fire_Sound;

	// FPS camera
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;

	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

};

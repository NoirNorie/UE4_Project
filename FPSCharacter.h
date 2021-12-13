// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// 카메라 관련 헤더
#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"

// 컨트롤 관련 헤더
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// 생성자 중 사용할 함수가 들어있는 헤더
#include "UObject/ConstructorHelpers.h"

// 사운드 관련 헤더
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

#include "FPSProjectile.h"

// 이 헤더가 반드시 아래에 있어야 한다
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
	//// 투사체 발사를 다룰 함수 정의
	//UFUNCTION()
	//	void Fire();

	// 좁은 공간에 PvP 가 아니므로 히트스캔과 유사한 사격 체계를 사용함
	FTimerHandle timer;
	UPROPERTY() bool isFiring;
	UFUNCTION()
		void StartFire();
	UFUNCTION()
		void StopFire();
	void Fire();

	// 달리기 함수 정의
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedMultiplier;

	UFUNCTION() 
		void StartRun();
	UFUNCTION() 
		void StopRun();

	// 사운드
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

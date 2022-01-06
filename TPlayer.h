// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// ĳ���� ���
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"

// ������ �ϰ� ī�޶� ���
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// ������ �����Լ� ���
#include "UObject/ConstructorHelpers.h"
// ���� ���� �׸��� ���� ���
#include "Engine/Canvas.h" 
// HUD ���
#include "PlayerHUD.h"
// ĳ���� �̵� ������Ʈ ���(�ӵ��� �޾ƿ��µ� �����
#include "GameFramework/CharacterMovementComponent.h"
// ���̷�Ż �޽� ������Ʈ ���
#include "Components/SkeletalMeshComponent.h"

// �������̽� ���
#include "TPlayerInterface.h"

// ���� ������Ʈ ���
#include "Components/AudioComponent.h"
// ���� ť ���
#include "Sound/SoundCue.h"

// ����� �ִϸ��̼� ���
#include "TAnimInstance.h"

// ����ü ���
#include "BaseProjectile.h"

// �ݵ�� �� �Ʒ����� �ϴ� ���
#include "TPlayer.generated.h"

UCLASS()
class PP_API ATPlayer : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	ATPlayer(); // ������


	// -- ���� -- 
	// ������ ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* TPSpringArm;
	// ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
	// �� ��ġ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USkeletalMeshComponent* Weapon_Socket; // ���� ���� ��ġ�� �� ��

	FTimerHandle timer;
	UPROPERTY() bool isFiring;

	// �޸��� �ӵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedMultiplier;

	// �������̽��� ���� ���� Ȯ�ο� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool CheckWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName WeaponName;

	// ���ؿ� ����� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool CheckAim;

	// ���� ���
	UPROPERTY(BlueprintReadOnly, Category = "Audio") // ���� ������Ʈ
		class UAudioComponent* AudioComponent;
	UPROPERTY(BlueprintReadOnly, Category = "Audio") // �� �Ҹ�
		class USoundCue* ShotCue;
	UPROPERTY(BlueprintReadOnly, Category = "Audio") // źâ�� �� ����� �Ҹ�
		class USoundCue* EmptyCue;

	// �ִϸ��̼� �ν��Ͻ� ����
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
		class UTAnimInstance* AnimInst;


	// ������ ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UAnimMontage* ReloadMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 player_ammo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 player_mag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsReloading;

	// ��� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset; // �ѱ� ��ġ�� ������

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABaseProjectile> ProjectileClass; // ����ü ����

		// -- ���� -- 

		// -- �Լ� --
		// - ���� �Լ�
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	// - ���� �Լ�

	// - Ŀ���� �Լ�
	// �̵� �Լ� ����
	UFUNCTION() void MoveForward(float v);
	UFUNCTION() void MoveRight(float v);

	// �޸��� �Լ� ����
	void Sprint();
	void StopSprinting();

	// �ൿ �Լ� ����
	UFUNCTION() void StartJump();
	UFUNCTION() void StopJump();

	// ������ �Լ� ����
	UFUNCTION() void StartAim();
	UFUNCTION() void StopAim();

	// ��� �Լ� ����
	UFUNCTION() void StartFire();
	UFUNCTION() void StopFire();
	UFUNCTION() void Fire();

	// ������ �Լ� ����
	UFUNCTION() void StartReload();
	UFUNCTION() void ReloadEnd();
	// - Ŀ���� �Լ�

	// ���� ��ȯ�� �Լ���
	bool GetWeaponCheck(); // ���� ���� ���� Ȯ��

	bool GetAimCheck(); // ���� ���� Ȯ��

	void WeaponSet();

	// -- �Լ� --

	TMap<FName, USkeletalMesh*> WeaponMap; // ���ڿ��� �νĵǴ� ���� �����Ѵ�.
};

// �����丵 ���߿� ���� �ڵ�
/*
	// �������̽����� �Լ��� �����´�
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CheckWeapon")
	//void Equip_WeaponItem();
	//virtual void Equip_WeaponItem_Implementation() override;

	// ��ȣ�ۿ� �Լ� ����
	//UFUNCTION() void PlayerInteraction();


*/
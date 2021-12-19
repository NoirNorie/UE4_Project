// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// ĳ���� ���
#include "GameFramework/Character.h"
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

// �������̽� ���
#include "TPlayerInterface.h"

// ���� ������Ʈ ���
#include "Components/AudioComponent.h"
// ���� ť ���
#include "Sound/SoundCue.h"

// ����� �ִϸ��̼� ���
#include "TAnimInstance.h"

// �ݵ�� �� �Ʒ����� �ϴ� ���
#include "TPlayer.generated.h"

// ITPlayerInterface�� TPlayerInterface�� �������̽��� ��ӹ��� �� , public ITPlayerInterface
UCLASS()
class PP_API ATPlayer : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	ATPlayer();

	// ������ ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* TPSpringArm;
	// ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	FTimerHandle timer;
	UPROPERTY() bool isFiring;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAcceess = "true"))
	//	class UKHUDWidget* HUDWidget;

	// �޸��� �ӵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedMultiplier;

	// �������̽��� ���� ���� Ȯ�ο� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool CheckWeapon;

	// ���ؿ� ����� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool CheckAim;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
	virtual void PostInitializeComponents() override;

	int32 player_ammo;

	// �������̽����� �Լ��� �����´�
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CheckWeapon")
	//void Equip_WeaponItem();
	//virtual void Equip_WeaponItem_Implementation() override;

	// ���� ��ȯ�� �Լ���
	bool GetWeaponCheck(); // ���� ���� ���� Ȯ��

	bool GetAimCheck(); // ���� ���� Ȯ��

};

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


// ĳ���� �̵� ������Ʈ ���(�ӵ��� �޾ƿ��µ� �����
#include "GameFramework/CharacterMovementComponent.h"

// �������̽� ���
#include "TPlayerInterface.h"

// �ݵ�� �� �Ʒ����� �ϴ� ���
#include "TPlayer.generated.h"

// ITPlayerInterface�� TPlayerInterface�� �������̽��� ��ӹ��� �� , public ITPlayerInterface
UCLASS()
class PP_API ATPlayer : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* TPSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	// Sets default values for this character's properties
	ATPlayer();

	// �޸��� �ӵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedMultiplier;

	// �������̽��� ���� ���� Ȯ�ο� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool CheckWeapon;

	// ���ؿ� ����� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool CheckAim;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// �޸��� �Լ�
	void Sprint();
	void StopSprinting();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// �̵�
	UFUNCTION() void MoveForward(float v);
	UFUNCTION() void MoveRight(float v);

	// �ൿ
	UFUNCTION() void StartJump();
	UFUNCTION() void StopJump();

	// ������
	UFUNCTION() void StartAim();
	UFUNCTION() void StopAim();

	// �������̽����� �Լ��� �����´�
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CheckWeapon")
	//void Equip_WeaponItem();
	//virtual void Equip_WeaponItem_Implementation() override;

	// ���� ��ȯ�� �Լ���
	bool GetWeaponCheck(); // ���� ���� ���� Ȯ��

	bool GetAimCheck(); // ���� ���� Ȯ��

};

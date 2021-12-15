// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// ������ �ϰ� ī�޶� ���
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// ������ �����Լ� ���
#include "UObject/ConstructorHelpers.h"

#include "TPlayer.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
	

};

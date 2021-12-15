// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// 스프링 암과 카메라 헤더
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// 생성자 보조함수 헤더
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

	// 이동
	UFUNCTION() void MoveForward(float v);
	UFUNCTION() void MoveRight(float v);

	// 행동
	UFUNCTION() void StartJump();
	UFUNCTION() void StopJump();
	

};

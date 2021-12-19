// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// 캐릭터 헤더
#include "GameFramework/Character.h"
// 스프링 암과 카메라 헤더
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// 생성자 보조함수 헤더
#include "UObject/ConstructorHelpers.h"
// 엔진 위에 그리기 위한 헤더
#include "Engine/Canvas.h" 
// HUD 헤더
#include "PlayerHUD.h"
// 캐릭터 이동 컴포넌트 헤더(속도를 받아오는데 사용함
#include "GameFramework/CharacterMovementComponent.h"

// 인터페이스 헤더
#include "TPlayerInterface.h"

// 사운드 컴포넌트 헤더
#include "Components/AudioComponent.h"
// 사운드 큐 헤더
#include "Sound/SoundCue.h"

// 사용자 애니메이션 헤더
#include "TAnimInstance.h"

// 반드시 맨 아래여야 하는 헤더
#include "TPlayer.generated.h"

// ITPlayerInterface는 TPlayerInterface의 인터페이스를 상속받은 것 , public ITPlayerInterface
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

	// 스프링 암
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* TPSpringArm;
	// 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	FTimerHandle timer;
	UPROPERTY() bool isFiring;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAcceess = "true"))
	//	class UKHUDWidget* HUDWidget;

	// 달리기 속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedMultiplier;

	// 인터페이스로 보낼 무기 확인용 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool CheckWeapon;

	// 조준에 사용할 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool CheckAim;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 이동 함수 선언
	UFUNCTION() void MoveForward(float v);
	UFUNCTION() void MoveRight(float v);

	// 달리기 함수 선언
	void Sprint();
	void StopSprinting();

	// 행동 함수 선언
	UFUNCTION() void StartJump();
	UFUNCTION() void StopJump();

	// 정조준 함수 선언
	UFUNCTION() void StartAim();
	UFUNCTION() void StopAim();

	// 사격 함수 선언
	UFUNCTION() void StartFire();
	UFUNCTION() void StopFire();
	UFUNCTION() void Fire();

	// 사운드 재생
	UPROPERTY(BlueprintReadOnly, Category = "Audio") // 사운드 컴포넌트
		class UAudioComponent* AudioComponent;
	UPROPERTY(BlueprintReadOnly, Category = "Audio") // 총 소리
		class USoundCue* ShotCue;
	UPROPERTY(BlueprintReadOnly, Category = "Audio") // 탄창이 빈 경우의 소리
		class USoundCue* EmptyCue;

	// 애니메이션 인스턴스 변수
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
		class UTAnimInstance* AnimInst;
	virtual void PostInitializeComponents() override;

	int32 player_ammo;

	// 인터페이스에서 함수를 가져온다
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CheckWeapon")
	//void Equip_WeaponItem();
	//virtual void Equip_WeaponItem_Implementation() override;

	// 변수 반환용 함수들
	bool GetWeaponCheck(); // 무기 장착 여부 확인

	bool GetAimCheck(); // 조준 여부 확인

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// 캐릭터 헤더
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"

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
// 스켈레탈 메시 컴포넌트 헤더
#include "Components/SkeletalMeshComponent.h"

// 인터페이스 헤더
#include "TPlayerInterface.h"

// 사운드 컴포넌트 헤더
#include "Components/AudioComponent.h"
// 사운드 큐 헤더
#include "Sound/SoundCue.h"

// 사용자 애니메이션 헤더
#include "TAnimInstance.h"

// 투사체 헤더
#include "BaseProjectile.h"

// 반드시 맨 아래여야 하는 헤더
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
	ATPlayer(); // 생성자


	// -- 변수 -- 
	// 스프링 암
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* TPSpringArm;
	// 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
	// 손 위치
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USkeletalMeshComponent* Weapon_Socket; // 무기 장착 위치가 될 곳

	FTimerHandle timer;
	UPROPERTY() bool isFiring;

	// 달리기 속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedMultiplier;

	// 인터페이스로 보낼 무기 확인용 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool CheckWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName WeaponName;

	// 조준에 사용할 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool CheckAim;

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


	// 재장전 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UAnimMontage* ReloadMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 player_ammo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 player_mag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsReloading;

	// 사격 관련 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset; // 총구 위치의 오프셋

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABaseProjectile> ProjectileClass; // 투사체 변수

		// -- 변수 -- 

		// -- 함수 --
		// - 엔진 함수
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	// - 엔진 함수

	// - 커스텀 함수
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

	// 재장전 함수 선언
	UFUNCTION() void StartReload();
	UFUNCTION() void ReloadEnd();
	// - 커스텀 함수

	// 변수 반환용 함수들
	bool GetWeaponCheck(); // 무기 장착 여부 확인

	bool GetAimCheck(); // 조준 여부 확인

	void WeaponSet();

	// -- 함수 --

	TMap<FName, USkeletalMesh*> WeaponMap; // 문자열로 인식되는 맵을 생성한다.
};

// 리팩토링 도중에 빼낸 코드
/*
	// 인터페이스에서 함수를 가져온다
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CheckWeapon")
	//void Equip_WeaponItem();
	//virtual void Equip_WeaponItem_Implementation() override;

	// 상호작용 함수 선언
	//UFUNCTION() void PlayerInteraction();


*/
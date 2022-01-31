// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// 캐릭터 헤더
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
// 카메라 관련 헤더
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
// 캐릭터의 이동 컴포넌트 헤더(속도 계산용)
#include "GameFramework/CharacterMovementComponent.h"
// 스켈레탈 메시 컴포넌트 헤더
#include "Components/SkeletalMeshComponent.h"
// 캡슐 컴포넌트 헤더
#include "Components/CapsuleComponent.h"

// 사운드 컴포넌트 헤더
#include "Components/AudioComponent.h"
// 사운드 큐 헤더
#include "Sound/SoundCue.h"

// 생성자 보조 함수 헤더
#include "UObject/ConstructorHelpers.h"
// 캐릭터 애니메이션 헤더
#include "TPlayerAnimInst.h"

// 캐릭터 인터페이스 헤더
#include "TPlayerInterface.h"

// 게임 플레이 헤더
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// 위젯 헤더
#include "Components/Widget.h"
#include "TPlayerStateWidget.h"
// 인벤토리 헤더
#include "InventoryBase.h"
// 위젯을 위해 가져올 게임모드 헤더
#include "PPGameModeBase.h"

// 플레이어 컨트롤러 헤더
#include "TPlayerController.h"


// 엔진 위에 그리기 위한 헤더
#include "Engine/Canvas.h" 
// 디버그 헤더
#include "DrawDebugHelpers.h"

#include "TPlayer.generated.h"

// 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnWeaponChangedDelegate);

UCLASS()
class PP_API ATPlayer : public ACharacter, public ITPlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPlayer(); // 캐릭터 생성자
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// -- 변수 -- 
	// 스프링 암
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* TPSpringArm;
	// 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TFollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		FVector CamOriginPos;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float CamArmLength;
	// 손 위치
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USkeletalMeshComponent* Weapon_Socket; // 무기 장착 위치가 될 곳

	FTimerHandle timer;
	UPROPERTY() 
		bool isFiring;

	// 달리기 속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedMultiplier;

	// 사운드 재생
	UPROPERTY(BlueprintReadOnly, Category = "Audio") // 사운드 컴포넌트
		class UAudioComponent* AudioComponent;
	UPROPERTY(BlueprintReadOnly, Category = "Audio") // 총 소리
		class USoundCue* ShotCue;
	UPROPERTY(BlueprintReadOnly, Category = "Audio") // 탄창이 빈 경우의 소리
		class USoundCue* EmptyCue;

	// 애니메이션 인스턴스 변수
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
		class UTPlayerAnimInst* AnimInst;

	// 사격 관련 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset; // 총구 위치의 오프셋
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
		float player_Damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
		float FireRate;

	// 히트 스캔을 위한 포인터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UGameplayStatics* GameStatic;

	// 위젯을 가져올 포인터
	class APPGameModeBase* GMD;
	class UTPlayerStateWidget* PlayerWidget;
	class UInventoryBase* Inventory;

	// -- 변수 -- 

	// -- 함수 --


public:	
	// 엔진 함수
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	// 엔진 함수

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

	// 인벤토리 함수 선언
	UFUNCTION() void InventoryToggle();

	// 변수 반환용 함수들
	bool GetWeaponCheck(); // 무기 장착 여부 확인
	bool GetAimCheck(); // 조준 여부 확인
	// void WeaponSet();

	// 데미지 처리를 위한 프레임워크 함수
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	// 무기 처리용 맵
	 TMap<FName, ConstructorHelpers::FObjectFinder<USkeletalMesh>> WeaponMap; // 문자열로 인식되는 맵을 생성한다.

	// 인터페이스 함수
	// 인터페이스 함수의 인터페이스
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface Call")
		void EquipWeaponItem(FName weapon_Name, int32 weaponAmmo, float weaponDamage, float weaponFireRate, int32 weaponIDX);
	// 인터페이스 함수의 구현
	virtual void EquipWeaponItem_Implementation(FName weapon_Name, int32 weaponAmmo, float weaponDamage, float weaponFireRate, int32 weaponIDX) override;

	// 인터페이스로 보낼 무기 확인용 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CheckWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName WeaponName;
	// 조준에 사용할 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool CheckAim;

	// 총알 장전 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 player_ammo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 player_mag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsReloading;

	// 캐릭터 상태 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float player_HP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float player_Hungry;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float player_Thirsty;

	// 에너지와 수분 소모량
	float RequireMoisture;
	float RequireFat;

	// 델리게이트
	FOnWeaponChangedDelegate OnWeaponNameChanged;

};
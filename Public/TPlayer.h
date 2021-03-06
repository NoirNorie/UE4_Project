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
// 라이트 컴포넌트 헤더
#include "Components/SpotLightComponent.h"
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
#include "GameProgressWidget.h"
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

// 파티클 헤더
#include "Particles/ParticleSystem.h"


#include "TPlayer.generated.h"

// 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnWeaponChangedDelegate);
DECLARE_DELEGATE(FDele_LootingStart);  // 줍기 시작을 알릴 델리게이트
DECLARE_DELEGATE(FDele_LootingCancle); // 줍기 취소를 알릴 델리게이트 

UCLASS()
class PP_API ATPlayer : public ACharacter, public ITPlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPlayer(); // 캐릭터 생성자
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float GateOpenProgress;


public:
	// --- 액터 변수 ----------------------------------------------------------------------------------------

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
	// 라이트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USpotLightComponent* PlayerLight;


	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//	class ATPlayercontrollter* PlayerCont;

	FTimerHandle timer;
	UPROPERTY() 
		bool isFiring;

	// 달리기 속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedMultiplier;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		bool bSprint;

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

	// 히트 스캔을 위한 게임스태틱 포인터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UGameplayStatics* GameStatic;

	// 총구 섬광 표현을 위한 변수
	UPROPERTY()
	class UParticleSystem* MuzzleParticle;
	// 총알 충돌 이펙트를 표현할 변수
	UPROPERTY()
	class UParticleSystem* ImpactParticle;


	// -------- 위젯 관련 포인터 ----------------------------------------------------------------------------------

	class APPGameModeBase* GMD;					// 게임모드
	class UTPlayerStateWidget* PlayerWidget;	// 플레이어 상태 창 위젯 포인터
	class UInventoryBase* Inventory;			// 인벤토리 위젯 포인터
	class UGameProgressWidget* ProgressWidget;  // 게임 진행 상황 위젯 포인터
	class UGameOverWidget* GameOverWidget;		// 게임 오버 위젯 포인터
	class UPauseWidget* PauseWidget;			// 정지 메뉴 위젯 포인터

	// ------------------------------------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ProgressComp;

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
	// 아이템 사용 함수
	UFUNCTION() void UseItem(int32 itemIdx, float Inc_HP, float Dec_Hungry, float Dec_Thirst);

	// 상호작용 함수 선언
	UFUNCTION() void StartInteraction();
	UFUNCTION() void StopInteraction();

	// 중지 메뉴 함수 선언
	UFUNCTION() void PauseToggle();

	// 조명 토글 함수 선언
	UFUNCTION() void LightToggle();

	// 변수 반환용 함수들
	bool GetWeaponCheck(); // 무기 장착 여부 확인
	bool GetAimCheck(); // 조준 여부 확인
	// void WeaponSet();

	// 데미지 처리를 위한 프레임워크 함수
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// 좀비를 공격했을 때 발생시킬 함수
	void ZombieAggro();

	// 사망 처리를 위한 함수
	void PlayerDeath();


	// 무기 처리용 맵
	 TMap<FName, ConstructorHelpers::FObjectFinder<USkeletalMesh>> WeaponMap; // 문자열로 인식되는 맵을 생성한다.

	// --- 인터페이스 함수 ----------------------------------------------------------------------------------------

	// 무기 획득 인터페이스 함수
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface Call")
		void EquipWeaponItem(FName weapon_Name, int32 weaponAmmo, float weaponDamage, float weaponFireRate, int32 weaponIDX);
	virtual void EquipWeaponItem_Implementation(FName weapon_Name, int32 weaponAmmo, float weaponDamage, float weaponFireRate, int32 weaponIDX) override;

	// 총알 획득 인터페이스 함수
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface Call")
		void GetAmmoItem(FName Ammo_Name, int32 Ammo_Type);
	virtual void GetAmmoItem_Implementation(FName Ammo_Name, int32 Ammo_Type);

	// 음식 아이템 획득 인터페이스 함수
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface Call")
		void GetFoodItem(FName Food_Name, float fHungry, float fThirst, int32 FoodType);
	virtual void GetFoodItem_Implementation(FName Food_Name, float fHungry, float fThirst, int32 FoodType);

	// ------------------------------------------------------------------------------------------------------------

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName CurrentAmmoName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsReloading;

	// 캐릭터 상태 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float player_HP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float player_Hungry;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float player_Thirsty;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool player_Death;

	// 조명 토글 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bLightCond;

	// 로드 변수
	bool GMD_Online;

	// 접촉 함수
	UFUNCTION() void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	AActor* ContactActor;


	// 에너지와 수분 소모량
	float RequireMoisture;
	float RequireFat;

	// 델리게이트
	FOnWeaponChangedDelegate OnWeaponNameChanged;
	FDele_LootingCancle OnLootingCancled;
	FDele_LootingStart OnLootingStarted;

};
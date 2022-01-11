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

// ���� �÷��� ���
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// ���� ���
#include "Components/Widget.h"

// ����� ���
#include "DrawDebugHelpers.h"

// ������-�κ��丮 ������ ����ü ����
#include "ItemEnumC.h"

// �ݵ�� �� �Ʒ����� �ϴ� ���
#include "TPlayer.generated.h"

// �������� ������
UENUM(BlueprintType)
enum class EItemType : uint8
{
	ITEM_None		UMETA(DisplayName = "None"),
	ITEM_Usable		UMETA(DisplayName = "Usable"),
	ITEM_Equipment	UMETA(DisplayName = "Equipment")
};

// �������� ����ü
USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()
public:
	FItemData() : Name(TEXT("")), Texture(nullptr), Type(EItemType::ITEM_None), Count(0) {};
	// �ʱ�ȭ ����Ʈ ����� ���� ���
	virtual void Use(ATPlayer* player) {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTexture2D *Texture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EItemType> Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Count;
};

UCLASS()
class PP_API ATPlayer : public ACharacter, public ITPlayerInterface
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
		class UCameraComponent* TFollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		FVector CamOriginPos;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float CamArmLength;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
		float player_Damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
		float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UGameplayStatics* GameStatic;

	// �κ��丮 ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TArray<FItemData> Inventory;


	//UPROPERTY(EditDefaultsOnly, Category = Projectile)
	//	TSubclassOf<class ABaseProjectile> ProjectileClass; // ����ü ����



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

	// �κ��丮 ���� �ݱ� �Լ�
	//UFUNCTION() void OpenInventory();

	// - Ŀ���� �Լ�

	// ���� ��ȯ�� �Լ���
	bool GetWeaponCheck(); // ���� ���� ���� Ȯ��
	bool GetAimCheck(); // ���� ���� Ȯ��
	void WeaponSet();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface Call")
	void EquipWeaponItem(FName weapon_Name, int32 weaponAmmo, float weaponDamage, float weaponFireRate, int32 weaponIDX);
	virtual void EquipWeaponItem_Implementation(FName weapon_Name, int32 weaponAmmo, float weaponDamage, float weaponFireRate, int32 weaponIDX) override;

	// -- �Լ� --

	TMap<FName, ConstructorHelpers::FObjectFinder<USkeletalMesh>> WeaponMap; // ���ڿ��� �νĵǴ� ���� �����Ѵ�.
};
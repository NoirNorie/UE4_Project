// Fill out your copyright notice in the Description page of Project Settings.

#include "TPlayer.h"

// Sets default values
ATPlayer::ATPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	//GetCharacterMovement()->JumpZVelocity = 450.0f;
	//GetCharacterMovement()->AirControl = 0.2f;
	//GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	TPSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TPSpringArm"));
	TPSpringArm->SetupAttachment(RootComponent);
	TPSpringArm->TargetArmLength = CamArmLength = 300.0f;
	CamOriginPos.X = 100.0f;
	CamOriginPos.Y = 50.0f;
	CamOriginPos.Z = 50.0f;
	TPSpringArm->bUsePawnControlRotation = true;

	TFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TFollowCamera"));
	TFollowCamera->SetupAttachment(TPSpringArm, USpringArmComponent::SocketName);
	TFollowCamera->bUsePawnControlRotation = false;

	

	FName weaponSocketName = TEXT("Socket_R_Hand");
	Weapon_Socket = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon_Socket->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, weaponSocketName);

	FireRate = 0.0f; // �ʱ� �߻� �ӵ��� ���Ⱑ �����Ƿ� 0.0f;

	// �ִϸ��̼� �������Ʈ �Ӽ� ����
	static ConstructorHelpers::FClassFinder<UAnimInstance>TPlayerAnim(TEXT(
		"AnimBlueprint'/Game/Blueprint/PlayerAnim.PlayerAnim'")
	);
	if (TPlayerAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(TPlayerAnim.Class);
	}

	// �޸��� ��� �ʱ�ȭ
	SprintSpeedMultiplier = 2.0f;

	// �������̽��� ���� ���� �ʱ�ȭ
	CheckWeapon = false;

	// ���� ť�� ����� ������Ʈ ����
	//static ConstructorHelpers::FObjectFinder<USoundCue>RifleShot(TEXT("SoundCue'/Game/Blueprint/WeaponSound/Rifle2_Cue.Rifle2_Cue'"));
	//if (RifleShot.Succeeded())
	//{
	//	ShotCue = RifleShot.Object;
	//	//ShotCue = Cast<USoundCue>;

	//}
	static ConstructorHelpers::FObjectFinder<USoundCue>RifleEmpty(TEXT("SoundCue'/Game/Blueprint/WeaponSound/RifleEmpty_Cue.RifleEmpty_Cue'"));
	if (RifleEmpty.Succeeded())
	{
		EmptyCue = RifleEmpty.Object;
	}
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PlayerAudio"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetupAttachment(RootComponent);


	// ����� ���⸦ �ʿ� ����� ���´�
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>WeaponSK1(TEXT("SkeletalMesh'/Game/Blueprint/SK_AR4_X.SK_AR4_X'"));
	if (WeaponSK1.Succeeded())
	{
		FName WeaponSKName = "AR-15";
		WeaponMap.Add(WeaponSKName, WeaponSK1);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>WeaponSK2(TEXT("SkeletalMesh'/Game/Blueprint/SK_KA47_X.SK_KA47_X'"));
	if (WeaponSK2.Succeeded())
	{
		FName WeaponSKName = "AK-47";
		WeaponMap.Add(WeaponSKName, WeaponSK2);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>WeaponSK3(TEXT("SkeletalMesh'/Game/Blueprint/SK_KA_Val_X.SK_KA_Val_X'"));
	if (WeaponSK3.Succeeded())
	{
		FName WeaponSKName = "KA-Val";
		WeaponMap.Add(WeaponSKName, WeaponSK3);
	}

	//// �κ��丮 �о����


	// ���� �̸� �ʱ�ȭ
	WeaponName = "-";
	// �Ѿ� �ʱ�ȭ
	player_ammo = 0; // �Ѿ� ��
	player_mag = 0; // źâ ��
}

// Called when the game starts or when spawned
void ATPlayer::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Play")));
}

// Called every frame
void ATPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// �̵� ���ε�
	PlayerInputComponent->BindAxis("MoveForward", this, &ATPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATPlayer::MoveRight);

	// ī�޶� ȸ�� ���ε�
	PlayerInputComponent->BindAxis("Turn", this, &ATPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ATPlayer::AddControllerPitchInput);

	// ���� ���ε�
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATPlayer::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATPlayer::StopJump);

	// �޸��� ���ε�
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ATPlayer::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ATPlayer::StopSprinting);

	// ������ ���ε�
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ATPlayer::StartAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ATPlayer::StopAim);

	// ��� ���ε�
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATPlayer::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATPlayer::StopFire);

	// ������ ���ε�
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ATPlayer::StartReload);

	// �κ��丮 ���� �ݱ� ���ε�
	//PlayerInputComponent->BindAction("OpenInventory", IE_Pressed, this, &ATPlayer::OpenInventory);
}

// �����̵� �Լ�
void ATPlayer::MoveForward(float v)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, v);
}
// �¿��̵� �Լ�
void ATPlayer::MoveRight(float v)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, v);
}

// ���� �Լ�
void ATPlayer::StartJump()
{
	bPressedJump = true;
}
void ATPlayer::StopJump()
{
	bPressedJump = false;
}

// �޸��� �Լ�
void ATPlayer::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}
void ATPlayer::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}

// ���� �Լ�
void ATPlayer::StartAim()
{
	TFollowCamera->SetFieldOfView(TFollowCamera->FieldOfView /= 2);
	CheckAim = true;
}
void ATPlayer::StopAim()
{
	TFollowCamera->SetFieldOfView(TFollowCamera->FieldOfView *= 2);
	CheckAim = false;
}

// �ִϸ��̼� ��¿� �Լ�
void ATPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInst = Cast<UTAnimInstance>(GetMesh()->GetAnimInstance());
}
// ���Ͱ� ���忡 �����ϱ� ���� �ܰ迡�� ȣ��Ǵ� �Լ�
// AnimInstance �ʱ�ȭ�� ������ �Լ�

// ��� �Լ� ����
void ATPlayer::StartFire()
{
	isFiring = true;
	Fire();
}
void ATPlayer::StopFire()
{
	isFiring = false;
}
void ATPlayer::Fire()
{
	if (isFiring == true && CheckWeapon == true)
	{
		if (player_ammo == 0) // �Ѿ��� ���� ��� ���� �Ҹ��� ������ �Ѵ�
		{
			AudioComponent->SetSound(EmptyCue);
			AudioComponent->Play();
		}

		if (player_ammo > 0)
		{

			// 1�� �浹 �˻�� ����

			FHitResult OutHit; // �浹 �˻縦 �� ����
			FVector Line1Start = TFollowCamera->GetComponentLocation(); // ������ ������
			FVector Line1FV = TFollowCamera->GetForwardVector(); // ������ ���� ����
			FVector Line1End = Line1Start + (Line1FV * 10000.0f); // ������ ����

			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(this); // �浹���� �� �÷��̾� ���͸� �����Ѵ�.
			DrawDebugLine(GetWorld(), Line1Start, Line1End, FColor::Green, true);
			bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Line1Start, Line1End, ECC_Visibility, CollisionParams);

			if (isHit)
			{
				if (OutHit.GetActor())
				{
					DrawDebugSolidBox(GetWorld(), OutHit.ImpactPoint, FVector(10.0f), FColor::Blue, true); // �ǰݵ� ������ �ڽ��� �׸���
					//UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *OutHit.GetActor()->GetName());
					//UE_LOG(LogTemp, Log, TEXT("Hit Bone : %s"), *OutHit.BoneName.ToString());
					AActor* HitActor = OutHit.GetActor();
					
					GameStatic->ApplyPointDamage(HitActor, player_Damage, HitActor->GetActorLocation(), OutHit, nullptr, this, nullptr); // �������� ���Ѵ�.

				}
			}

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Fire")));

			// ���� ����� �ִϸ��̼� ��Ƽ���̿� �����ߴ�
			// �Ҹ��� ��ø�� �� �ֵ��� ó����
			AnimInst->PlayFire(); // ��� ����� ���۽�Ų��.
			// �Ѿ��� ��Ƽ���� �Լ����� �����Ѵ�
			GetWorld()->GetTimerManager().SetTimer(timer, this, &ATPlayer::Fire, FireRate, false);
		}
	}
}

// ������ �Լ� ����
void ATPlayer::StartReload()
{
	if (player_mag != 0 && CheckWeapon == true)
	{
		AnimInst->PlayReload(); // ������ ����� ���۽�Ų��
		// ������ �� źâ�� ��Ƽ���� �Լ����� �����Ѵ�.
		IsReloading = true;
	}
}
void ATPlayer::ReloadEnd()
{
	IsReloading = false;
}

// �κ��丮 �Լ� ����
//void ATPlayer::OpenInventory()
//{
//	if (Inventory->IsVisible())
//	{
//		Inventory->VisibleInventory(ESlateVisibility::Collapsed);
//	}
//	else
//	{
//		Inventory->VisibleInventory(ESlateVisibility::Visible);
//	}
//}



// ���� ���� ����� ������ �Լ�
bool ATPlayer::GetWeaponCheck()
{
	return CheckWeapon;
}
// ���� ���θ� ������ �Լ�
bool ATPlayer::GetAimCheck()
{
	return CheckAim;
}

void ATPlayer::EquipWeaponItem_Implementation(FName weapon_Name, int32 weaponAmmo, float weaponDamage, float weaponFireRate, int32 weaponIDX)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Interface Called")));
	WeaponName = weapon_Name;
	player_ammo = weaponAmmo;
	player_Damage = weaponDamage;
	FireRate = weaponFireRate;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Damage %f"), player_Damage));
	AnimInst->shotIDX = weaponIDX;


	USkeletalMesh* CurrentWeapon = WeaponMap.Find(WeaponName)->Object;
	Weapon_Socket->SetSkeletalMesh(CurrentWeapon);
	CheckWeapon = true;
}

// �ڵ� ���� �� ���� ��

//void ATPlayer::WeaponSet()
//{
//	FName ARName = "AR15";
//	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Tmp(TEXT("SkeletalMesh'/Game/Blueprint/SK_AR4_X.SK_AR4_X'"));
//	USkeletalMesh* ARX = Tmp.Object;
//	WeaponMap.Add(ARName, ARX);
//}


//FVector Gun_Direction;		
//CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);		
//Weapon_Socket->GetSocketLocation(TEXT("Socket_R_Hand"));		
//FRotator MuzzleRotation = CameraRotation;

//FVector MuzzleLocation = CharacterMesh->GetSocketLocation(TEXT("Socket_R_Hand"));
//FRotator MuzzleRotation = CharacterMesh->GetSocketRotation(TEXT("Socket_R_Hand"));

//FVector MuzzleLocation = Weapon_Socket->GetSocketLocation(TEXT("Socket_MuzzleLoc"));
//FRotator MuzzleRotation = Weapon_Socket->GetSocketRotation(TEXT("Socket_MuzzleLoc"));

//// ��Ÿ�� �ʱ�ȭ
//static ConstructorHelpers::FObjectFinder<UAnimMontage>Reload(TEXT(""));
//if (Reload.Succeeded())
//{
//	ReloadMontage = Reload.Object;
//}
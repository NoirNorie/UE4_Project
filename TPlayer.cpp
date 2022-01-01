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
	TPSpringArm->TargetArmLength = 300.0f;
	TPSpringArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCmaera"));
	FollowCamera->SetupAttachment(TPSpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	CharacterMesh->SetupAttachment(RootComponent);
	
	Weapon_Socket = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon_Socket->SetupAttachment(CharacterMesh);

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
	static ConstructorHelpers::FObjectFinder<USoundCue>RifleShot(TEXT("SoundCue'/Game/Blueprint/WeaponSound/Rifle2_Cue.Rifle2_Cue'"));
	if (RifleShot.Succeeded())
	{
		ShotCue = RifleShot.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundCue>RifleEmpty(TEXT("SoundCue'/Game/Blueprint/WeaponSound/RifleEmpty_Cue.RifleEmpty_Cue'"));
	if (RifleEmpty.Succeeded())
	{
		EmptyCue = RifleEmpty.Object;
	}
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PlayerAudio"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetupAttachment(RootComponent);

	// ���� �̸� �ʱ�ȭ
	WeaponName = "-";

	// �Ѿ� �ʱ�ȭ
	player_ammo = 30; // �Ѿ� ��
	player_mag = 3; // źâ ��

	// ��Ÿ�� �ʱ�ȭ
	static ConstructorHelpers::FObjectFinder<UAnimMontage>Reload(TEXT(""));
	if (Reload.Succeeded())
	{
		ReloadMontage = Reload.Object;
	}

	WeaponSet();

}

// Called when the game starts or when spawned
void ATPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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
	PlayerInputComponent->BindAxis("LookUp", this, & ATPlayer::AddControllerPitchInput);

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
	FollowCamera->SetFieldOfView(FollowCamera->FieldOfView /= 2);
	CheckAim = true;
}
void ATPlayer::StopAim()
{
	FollowCamera->SetFieldOfView(FollowCamera->FieldOfView *= 2);
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
		if (ProjectileClass)
		{
			FVector CameraLocation;
			FRotator CameraRotation;
			GetActorEyesViewPoint(CameraLocation, CameraRotation);
			//FVector Gun_Direction;		
			//CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);		
			//Weapon_Socket->GetSocketLocation(TEXT("Socket_R_Hand"));		
			//FRotator MuzzleRotation = CameraRotation;

			if (Weapon_Socket) // ���⸦ ȹ���Ͽ��ٸ�
			{
				//FVector MuzzleLocation = CharacterMesh->GetSocketLocation(TEXT("Socket_R_Hand"));
				//FRotator MuzzleRotation = CharacterMesh->GetSocketRotation(TEXT("Socket_R_Hand"));

				//FVector MuzzleLocation = Weapon_Socket->GetSocketLocation(TEXT("Socket_MuzzleLoc"));
				//FRotator MuzzleRotation = Weapon_Socket->GetSocketRotation(TEXT("Socket_MuzzleLoc"));
				FVector MuzzleLocation = Weapon_Socket->GetSocketLocation(TEXT("Socket_Root"));
				FRotator MuzzleRotation = Weapon_Socket->GetSocketRotation(TEXT("Socket_Root"));
				MuzzleRotation.Yaw += 90; // ���̷��� �޽� ����� ��ġ��Ű�� ���� 90���� �����ش�.

				MuzzleRotation.Pitch += CameraRotation.Pitch;

				UWorld* World = GetWorld();
				if (World)
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					SpawnParams.Instigator = GetInstigator();
					ABaseProjectile* Projectile = World->SpawnActor<ABaseProjectile>(
						ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams
						);
					if (Projectile)
					{
						FVector LaunchDirection = MuzzleRotation.Vector();
						Projectile->FireInDirection(LaunchDirection);
					}
				}
			}

			//FVector WeaponLocation = ;
			//MuzzleLocation.Y += 60;
			//MuzzleRotation.Pitch += 10.0f;
			
			
		}


		if (player_ammo == 0)
		{
			AudioComponent->SetSound(EmptyCue);
			AudioComponent->Play();
		}

		if (player_ammo > 0)
		{
			// ���� ����� �ִϸ��̼� ��Ƽ���̿� �����ߴ�
			// �Ҹ��� ��ø�� �� �ֵ��� ó����
			AnimInst->PlayFire(); // ��� ����� ���۽�Ų��.
			// �Ѿ��� ��Ƽ���� �Լ����� �����Ѵ�
			GetWorld()->GetTimerManager().SetTimer(timer, this, &ATPlayer::Fire, 0.1f, false);

			

		}

	}
}

// ������ �Լ� ����
void ATPlayer::StartReload()
{
	if (player_mag != 0 && CheckWeapon == true)
	{
		//CheckAim = false; // ���� �� ������ Ǭ��
		AnimInst->PlayReload(); // ������ ����� ���۽�Ų��
		// ������ �� źâ�� ��Ƽ���� �Լ����� �����Ѵ�.
		IsReloading = true;
	}
}
void ATPlayer::ReloadEnd()
{
	IsReloading = false;
}

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

void ATPlayer::WeaponSet()
{
	FName ARName = "AR15";
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Tmp(TEXT("SkeletalMesh'/Game/Blueprint/SK_AR4_X.SK_AR4_X'"));
	USkeletalMesh* ARX = Tmp.Object;
	WeaponMap.Add(ARName, ARX);
}
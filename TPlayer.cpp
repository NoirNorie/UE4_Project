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

	// �Ѿ� �ʱ�ȭ
	player_ammo = 30; // �Ѿ� ��
	player_mag = 3; // źâ ��

	// ��Ÿ�� �ʱ�ȭ
	static ConstructorHelpers::FObjectFinder<UAnimMontage>Reload(TEXT(""));
	if (Reload.Succeeded())
	{
		ReloadMontage = Reload.Object;
	}
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

void ATPlayer::MoveForward(float v)
{

	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	
	AddMovementInput(Direction, v);
}

void ATPlayer::MoveRight(float v)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, v);
}

void ATPlayer::StartJump()
{
	bPressedJump = true;
}
void ATPlayer::StopJump()
{
	bPressedJump = false;
}

// �޸��� �Լ� ����
void ATPlayer::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}
void ATPlayer::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}

// ���� �Լ� ����
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



// ��� �ִϸ��̼� ��¿�
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
		if (player_ammo == 0)
		{
			AudioComponent->SetSound(EmptyCue);
			AudioComponent->Play();
		}

		if (player_ammo > 0)
		{
			player_ammo--;
			//AudioComponent->SetSound(ShotCue);
			//AudioComponent->Play();
			AnimInst->PlayFire();
			GetWorld()->GetTimerManager().SetTimer(timer, this, &ATPlayer::Fire, 0.1f, false);
			UE_LOG(LogTemp, Log, TEXT("Ammo : %d"), player_ammo);
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
		IsReloading = true;
	}
}
void ATPlayer::ReloadEnd()
{
	IsReloading = false;
}


bool ATPlayer::GetWeaponCheck()
{
	return CheckWeapon;
}

bool ATPlayer::GetAimCheck()
{
	return CheckAim;
}
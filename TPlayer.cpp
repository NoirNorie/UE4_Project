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

	// 애니메이션 블루프린트 속성 시정
	static ConstructorHelpers::FClassFinder<UAnimInstance>TPlayerAnim(TEXT(
		"AnimBlueprint'/Game/Blueprint/PlayerAnim.PlayerAnim'")
	);
	if (TPlayerAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(TPlayerAnim.Class);
	}

	// 달리기 배속 초기화
	SprintSpeedMultiplier = 2.0f;

	// 인터페이스로 보낼 변수 초기화
	CheckWeapon = false;

	// 사운드 큐와 오디어 컴포넌트 설정
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

	// 무기 이름 초기화
	WeaponName = "-";

	// 총알 초기화
	player_ammo = 30; // 총알 수
	player_mag = 3; // 탄창 수

	// 몽타주 초기화
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

	// 이동 바인드
	PlayerInputComponent->BindAxis("MoveForward", this, &ATPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATPlayer::MoveRight);

	// 카메라 회전 바인드
	PlayerInputComponent->BindAxis("Turn", this, &ATPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, & ATPlayer::AddControllerPitchInput);

	// 점프 바인드
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATPlayer::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATPlayer::StopJump);

	// 달리기 바인드
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ATPlayer::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ATPlayer::StopSprinting);

	// 정조준 바인드
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ATPlayer::StartAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ATPlayer::StopAim);

	// 사격 바인드
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATPlayer::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATPlayer::StopFire);

	// 재장전 바인드
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ATPlayer::StartReload);
}

// 전후이동 함수
void ATPlayer::MoveForward(float v)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);	
	AddMovementInput(Direction, v);
}
// 좌우이동 함수
void ATPlayer::MoveRight(float v)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, v);
}

// 점프 함수
void ATPlayer::StartJump()
{
	bPressedJump = true;
}
void ATPlayer::StopJump()
{
	bPressedJump = false;
}

// 달리기 함수
void ATPlayer::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}
void ATPlayer::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}

// 조준 함수
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

// 애니메이션 출력용 함수
void ATPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInst = Cast<UTAnimInstance>(GetMesh()->GetAnimInstance());
}
// 액터가 월드에 등장하기 최종 단계에서 호출되는 함수
// AnimInstance 초기화에 적합한 함수

// 사격 함수 구현
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

			if (Weapon_Socket) // 무기를 획득하였다면
			{
				//FVector MuzzleLocation = CharacterMesh->GetSocketLocation(TEXT("Socket_R_Hand"));
				//FRotator MuzzleRotation = CharacterMesh->GetSocketRotation(TEXT("Socket_R_Hand"));

				//FVector MuzzleLocation = Weapon_Socket->GetSocketLocation(TEXT("Socket_MuzzleLoc"));
				//FRotator MuzzleRotation = Weapon_Socket->GetSocketRotation(TEXT("Socket_MuzzleLoc"));
				FVector MuzzleLocation = Weapon_Socket->GetSocketLocation(TEXT("Socket_Root"));
				FRotator MuzzleRotation = Weapon_Socket->GetSocketRotation(TEXT("Socket_Root"));
				MuzzleRotation.Yaw += 90; // 스켈레톤 메시 방향과 일치시키기 위해 90도를 돌려준다.

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
			// 사운드 재생은 애니메이션 노티파이에 부착했다
			// 소리가 중첩될 수 있도록 처리함
			AnimInst->PlayFire(); // 사격 모션을 동작시킨다.
			// 총알은 노티파이 함수에서 감소한다
			GetWorld()->GetTimerManager().SetTimer(timer, this, &ATPlayer::Fire, 0.1f, false);

			

		}

	}
}

// 재장전 함수 구현
void ATPlayer::StartReload()
{
	if (player_mag != 0 && CheckWeapon == true)
	{
		//CheckAim = false; // 장전 중 조준을 푼다
		AnimInst->PlayReload(); // 재장전 모션을 동작시킨다
		// 재장전 시 탄창은 노티파이 함수에서 감소한다.
		IsReloading = true;
	}
}
void ATPlayer::ReloadEnd()
{
	IsReloading = false;
}

// 무기 장착 사실을 전달할 함수
bool ATPlayer::GetWeaponCheck()
{
	return CheckWeapon;
}
// 조준 여부를 전달할 함수
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
// Fill out your copyright notice in the Description page of Project Settings.


#include "TPlayer.h"

// Sets default values
ATPlayer::ATPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FireRate = 0; // 초기 발사 속도는 무기가 없으므로 0.0f;

	// 달리기 배속 초기화
	SprintSpeedMultiplier = 2.0f;

	// 무기 장착 상태 표시
	CheckWeapon = false;

	// 무기 이름 초기화
	WeaponName = "-";
	// 총알 초기화
	player_ammo = 0; // 총알 수
	player_mag = 0; // 탄창 수

	// 캐릭터 상태 초기화
	player_HP = 100.0f;
	player_Hungry = 0.0f;
	player_Thirsty = 0.0f;

	// 스프링암
	TPSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TPSpringArm"));
	TPSpringArm->SetupAttachment(RootComponent);
	TPSpringArm->TargetArmLength = CamArmLength = 300.0f;
	CamOriginPos.X = 100.0f;
	CamOriginPos.Y = 50.0f;
	CamOriginPos.Z = 50.0f;
	TPSpringArm->bUsePawnControlRotation = true;

	// 카메라
	TFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TFollowCamera"));
	TFollowCamera->SetupAttachment(TPSpringArm, USpringArmComponent::SocketName);
	TFollowCamera->bUsePawnControlRotation = false;

	// 무기 소켓 - 손
	FName weaponSocketName = TEXT("Socket_R_Hand");
	Weapon_Socket = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon_Socket->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, weaponSocketName);



	static ConstructorHelpers::FObjectFinder<USoundCue>RifleEmpty(TEXT("SoundCue'/Game/Blueprint/WeaponSound/RifleEmpty_Cue.RifleEmpty_Cue'"));
	if (RifleEmpty.Succeeded())
	{
		EmptyCue = RifleEmpty.Object;
	}
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PlayerAudio"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetupAttachment(RootComponent);

	// 사용할 무기를 맵에 기록해 놓는다
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
		FName WeaponSKName = "As-Val";
		WeaponMap.Add(WeaponSKName, WeaponSK3);
	}



}

// Called when the game starts or when spawned
void ATPlayer::BeginPlay()
{
	Super::BeginPlay();
	// 디버그 메시지
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Play")));

	UWorld* const world = GetWorld();
	if (world) // 월드 유효성 검사
	{
		if (APPGameModeBase* myGmd = Cast<APPGameModeBase>(GetWorld()->GetAuthGameMode())) // 게임모드 포인터 유효성 검사
		{
			GMD = myGmd;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("GMD ON")));

			// 게임모드에서 위젯을 가져온다.
			PlayerWidget = GMD->GetPlayerStateWidget();
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Widget Called")));
			if (PlayerWidget)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Player Widget Called")));
				PlayerWidget->SetWeaponName(WeaponName);
			}
		}
	}
	

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
	PlayerInputComponent->BindAxis("LookUp", this, &ATPlayer::AddControllerPitchInput);
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
	TFollowCamera->SetFieldOfView(TFollowCamera->FieldOfView /= 2);
	CheckAim = true;
	AnimInst->Aiming = true;
}
void ATPlayer::StopAim()
{
	TFollowCamera->SetFieldOfView(TFollowCamera->FieldOfView *= 2);
	CheckAim = false;
	AnimInst->Aiming = false;
}
// 애니메이션 출력용 함수
void ATPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInst = Cast<UTPlayerAnimInst>(GetMesh()->GetAnimInstance());
}
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
		if (player_ammo == 0) // 총알이 없는 경우 공이 소리만 나도록 한다
		{
			AudioComponent->SetSound(EmptyCue);
			AudioComponent->Play();
		}

		if (player_ammo > 0)
		{

			// 1차 충돌 검사용 선분

			FHitResult OutHit; // 충돌 검사를 할 변수
			FVector Line1Start = TFollowCamera->GetComponentLocation(); // 선분의 시작점
			FVector Line1FV = TFollowCamera->GetForwardVector(); // 선분의 방향 벡터
			FVector Line1End = Line1Start + (Line1FV * 10000.0f); // 선분의 끝점

			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(this); // 충돌에서 이 플레이어 액터를 제외한다.
			DrawDebugLine(GetWorld(), Line1Start, Line1End, FColor::Green, true);
			bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Line1Start, Line1End, ECC_Visibility, CollisionParams);

			if (isHit)
			{
				//if (OutHit.GetActor()->ActorHasTag("Monster"))
				if(OutHit.GetActor())
				{
					DrawDebugSolidBox(GetWorld(), OutHit.ImpactPoint, FVector(10.0f), FColor::Blue, true); // 피격된 지점에 박스를 그린다
					UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *OutHit.GetActor()->GetName());
					UE_LOG(LogTemp, Log, TEXT("Hit Bone : %s"), *OutHit.BoneName.ToString());
					AActor* HitActor = OutHit.GetActor();

					GameStatic->ApplyPointDamage(HitActor, player_Damage, HitActor->GetActorLocation(), OutHit, nullptr, this, nullptr); // 데미지를 가한다.
				}
			}

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Fire")));

			// 사운드 재생은 애니메이션 노티파이에 부착했다
			// 소리가 중첩될 수 있도록 처리함
			AnimInst->PlayFire(); // 사격 모션을 동작시킨다.
			// 총알은 노티파이 함수에서 감소한다
			GetWorld()->GetTimerManager().SetTimer(timer, this, &ATPlayer::Fire, FireRate, false);
		}
	}
}
// 재장전 함수 구현
void ATPlayer::StartReload()
{
	if (player_mag != 0 && CheckWeapon == true)
	{
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

// 무기 장착 인터페이스 함수
void ATPlayer::EquipWeaponItem_Implementation(FName weapon_Name, int32 weaponAmmo, float weaponDamage, float weaponFireRate, int32 weaponIDX)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Interface Called")));
	
	WeaponName = weapon_Name;
	if (PlayerWidget)
	{
		PlayerWidget->SetWeaponName(WeaponName);
	}


	player_ammo = weaponAmmo;
	player_Damage = weaponDamage;
	FireRate = weaponFireRate;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Damage %f"), player_Damage));
	AnimInst->ShotIDX = weaponIDX;

	USkeletalMesh* CurrentWeapon = WeaponMap.Find(WeaponName)->Object;
	if (CurrentWeapon != nullptr)
	{
		Weapon_Socket->SetSkeletalMesh(CurrentWeapon);
		CheckWeapon = true;
		AnimInst->WeaponState = true;
	}
}
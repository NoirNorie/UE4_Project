// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 5-1: 1인칭 카메라 조절 시작
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);
	// 카메라 컴포넌트를 캡슐 컴포넌트에 부착한다
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	// 카메라의 위치를 눈의 살짝 위에 배치한다
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// 폰이 카메라를 회전할 수 있도록 만듦
	FPSCameraComponent->bUsePawnControlRotation = true;

	// 6-1: 1인칭 메시 컴포넌트를 생성한다
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// 소유한 플레이어에게만 보이도록 설정
	FPSMesh->SetOnlyOwnerSee(true);
	// FPS 메시와 FPS 카메라를 부착한다
	FPSMesh->SetupAttachment(FPSCameraComponent);
	// 아직 뭔지 모르겠음
	// 환경적 요인으로 인해 무슨 문제가 생기는 것을 막기 위해 그림자를 제어하는 것 같음
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// 소유 플레이어가 몸체를 보지 못하도록 함
	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 1: 캐릭터 구현을 위한 첫 단계
	// - FPSCharacter 클래스가 사용될 것이라고 인증하는 부분
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	// 여기까지 정상적으로 수행하고 BP를 생성
	// 게임 모드에서 기본 폰 클래스를 BP_FPSCharacter로 만든 경우 움직이지 않을 것이고 이 상태가 정상 상태
	// 에디터에서 키 매핑을 수행해야 한다

	// 키 매핑을 수행하고 FPSCharacter 헤더 파일에서 선언을 하고 와야 한다

}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 2-1: 캐릭터 이동을 위한 단계
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// 3-1: 카메라 이동을 위한 단계
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, & AFPSCharacter::AddControllerPitchInput);

	// 4-1: 캐릭터 행동을 위한 단계
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);
}

// 2-2: 캐릭터 입력 처리를 위한 함수들 구현
void AFPSCharacter::MoveForward(float Value)
{
	// 플레이어가 이동하기 원하는 방향인지를 위해서 어느 방향이 '앞'인지를 찾고 기록한다
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}
void AFPSCharacter::MoveRight(float Value)
{
	// 플레이어가 이동하기 원하는 방향인지를 위해서 어느 방향이 '우측'인지를 찾고 기록한다
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

// 3-2: 카메라 이동 처리를 위한 함수
// 구현할 사항이 없음 (내장 함수인 것 같음)

// 4-2: 캐릭터 행동을 위한 함수들 구현
void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}
void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

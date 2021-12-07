// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 5-1: 1��Ī ī�޶� ���� ����
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);
	// ī�޶� ������Ʈ�� ĸ�� ������Ʈ�� �����Ѵ�
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	// ī�޶��� ��ġ�� ���� ��¦ ���� ��ġ�Ѵ�
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// ���� ī�޶� ȸ���� �� �ֵ��� ����
	FPSCameraComponent->bUsePawnControlRotation = true;

	// 6-1: 1��Ī �޽� ������Ʈ�� �����Ѵ�
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// ������ �÷��̾�Ը� ���̵��� ����
	FPSMesh->SetOnlyOwnerSee(true);
	// FPS �޽ÿ� FPS ī�޶� �����Ѵ�
	FPSMesh->SetupAttachment(FPSCameraComponent);
	// ���� ���� �𸣰���
	// ȯ���� �������� ���� ���� ������ ����� ���� ���� ���� �׸��ڸ� �����ϴ� �� ����
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// ���� �÷��̾ ��ü�� ���� ���ϵ��� ��
	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 1: ĳ���� ������ ���� ù �ܰ�
	// - FPSCharacter Ŭ������ ���� ���̶�� �����ϴ� �κ�
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	// ������� ���������� �����ϰ� BP�� ����
	// ���� ��忡�� �⺻ �� Ŭ������ BP_FPSCharacter�� ���� ��� �������� ���� ���̰� �� ���°� ���� ����
	// �����Ϳ��� Ű ������ �����ؾ� �Ѵ�

	// Ű ������ �����ϰ� FPSCharacter ��� ���Ͽ��� ������ �ϰ� �;� �Ѵ�

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

	// 2-1: ĳ���� �̵��� ���� �ܰ�
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// 3-1: ī�޶� �̵��� ���� �ܰ�
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, & AFPSCharacter::AddControllerPitchInput);

	// 4-1: ĳ���� �ൿ�� ���� �ܰ�
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);
}

// 2-2: ĳ���� �Է� ó���� ���� �Լ��� ����
void AFPSCharacter::MoveForward(float Value)
{
	// �÷��̾ �̵��ϱ� ���ϴ� ���������� ���ؼ� ��� ������ '��'������ ã�� ����Ѵ�
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}
void AFPSCharacter::MoveRight(float Value)
{
	// �÷��̾ �̵��ϱ� ���ϴ� ���������� ���ؼ� ��� ������ '����'������ ã�� ����Ѵ�
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

// 3-2: ī�޶� �̵� ó���� ���� �Լ�
// ������ ������ ���� (���� �Լ��� �� ����)

// 4-2: ĳ���� �ൿ�� ���� �Լ��� ����
void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}
void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

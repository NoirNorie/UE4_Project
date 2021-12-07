// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// 1��Ī ī�޶� ������ ���� ��� �߰�
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// �ݵ�� �Ʒ� ����� ���� �Ʒ��� ��ġ�ؾ� �Ѵ�
#include "FPSCharacter.generated.h"


UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY() // ������ ���⼭ ���� ���� �������� �����ص� ��� ����

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 2-0: ĳ���� �̵� ����
	// �����Ϳ��� Ű ������ �����ؾ� �Ѵ�.
	UFUNCTION() void MoveForward(float Value);
	UFUNCTION() void MoveRight(float Value);

	// 3-0: �þ� �̵�
	// �����Ϳ��� Ű ������ �����ؾ� �Ѵ�
	// �þ� �̵��� ���� �Լ����� ������ ���ʿ��� �� ����

	// 4-0: ĳ���� �ൿ ����
	// �����Ϳ��� Ű ������ �����ؾ� �Ѵ� (������ �׼� ����)
	UFUNCTION() void StartJump(); // Ű�� ���� �� ���� �÷��׸� Ų��
	UFUNCTION() void StopJump();  // Ű���� ���� ������ �� ���� �÷��׸� ����


	// 5-0: 1��Ī ī�޶� ����
	UPROPERTY(VisibleAnywhere) 
	class UCameraComponent* FPSCameraComponent;

	// 6-0: ����ƽ �޽� �߰�
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) 
	class USkeletalMeshComponent* FPSMesh;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// 1인칭 카메라 설정을 위한 헤더 추가
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// 반드시 아래 헤더가 가장 아래에 위치해야 한다
#include "FPSCharacter.generated.h"


UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY() // 가끔씩 여기서 빨간 줄이 그이지만 무시해도 상관 없다

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

	// 2-0: 캐릭터 이동 선언
	// 에디터에서 키 매핑을 선행해야 한다.
	UFUNCTION() void MoveForward(float Value);
	UFUNCTION() void MoveRight(float Value);

	// 3-0: 시야 이동
	// 에디터에서 키 매핑을 선행해야 한다
	// 시야 이동은 내장 함수여서 선언이 불필요한 것 같음

	// 4-0: 캐릭터 행동 선언
	// 에디터에서 키 매핑을 선행해야 한다 (점프는 액션 매핑)
	UFUNCTION() void StartJump(); // 키를 누를 때 점프 플래그를 킨다
	UFUNCTION() void StopJump();  // 키에서 손을 떼었을 때 점프 플래그를 제거


	// 5-0: 1인칭 카메라 조절
	UPROPERTY(VisibleAnywhere) 
	class UCameraComponent* FPSCameraComponent;

	// 6-0: 스태틱 메시 추가
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) 
	class USkeletalMeshComponent* FPSMesh;

};

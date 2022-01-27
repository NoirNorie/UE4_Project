// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// 생성자 보조 함수
#include "UObject/ConstructorHelpers.h"

// 오브젝트와 컴포넌트 헤더
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/Class.h"

#include "DrawDebugHelpers.h"

// 좀비 관련 헤더
#include "ZombieController.h"
#include "ZombieAnim.h"

#include "AZombie.generated.h"

// 델리게이트 선언
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate); // 공격 종료
DECLARE_MULTICAST_DELEGATE(FOnDetectEndDelegate); // 추적 종료

// ZombieAttack의 트레이스 채널
// ECC_GameTraceChannel1
// TPlayer의 오브젝트 채널
// ECC_GameTraceChannel2

UCLASS()
class PP_API AAZombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAZombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AttackCheck();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
		class UZombieAnim* ZombieAnimInst;


	UFUNCTION() void Attack();
	UFUNCTION() void Detect();
	UFUNCTION() void Death();

	FOnAttackEndDelegate OnAttackEnd;
	UFUNCTION() void OnAttackEnded(); 
	FOnDetectEndDelegate OnDetectEnd;
	UFUNCTION() void OnDetectEnded();

	UPROPERTY() bool IsAttacking;
	UPROPERTY() bool IsDetect;

	UPROPERTY() float Zombie_HP;
	UPROPERTY() bool IsDeath;
	UPROPERTY() bool bEndOverlapEnable;

	UPROPERTY() float AttackRange;
	UPROPERTY() float AttackRadius;


};

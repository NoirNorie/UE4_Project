// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


// 생성자 보조함수 헤더
#include "UObject/ConstructorHelpers.h"
// 캡슐 컴포넌트 헤더
#include "Components/CapsuleComponent.h"
// 스태틱 메시 컴포넌트 헤더
#include "Components/StaticMeshComponent.h"
// 스켈레탈 메시 컴포넌트 헤더
#include "Components/SkeletalMeshComponent.h"

#include "WeaponBase.generated.h"

// 무기 정보의 베이스 클래스

UCLASS()
class PP_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Casule, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* W_Contact; // 충돌 범위 지정에 사용할 캡슐 컴포넌트
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	//	class UStaticMeshComponent* W_Mesh; // 메시 표현에 사용할 스태틱 메시 컴포넌트
	// 총을 스켈레탈 메시로 표현 가능해서 추가함
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* SK_Mesh; // 메시 표현에 사용할 스켈레탈 메시 컴포넌트

	// 총알 정보
	// BlueprintReadOnly 매개변수는 private에서 못쓴다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Info: Ammo")
		float W_Ammo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Info: Ammo")
		float MAXW_Ammo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Info: Ammo")
		float CurrentW_Ammo;

};

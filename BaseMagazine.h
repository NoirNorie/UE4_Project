// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// 캡슐 컴포넌트 헤더
#include "Components/CapsuleComponent.h"
// 스태틱 메시 컴포넌트 헤더
#include "Components/StaticMeshComponent.h"

#include "BaseMagazine.generated.h"

UCLASS()
class PP_API ABaseMagazine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseMagazine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Casule, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* Mag_Capsule; // 충돌 범위 지정에 사용할 캡슐 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mag_Mesh; // 메시 표현에 사용할 스태틱 메시 컴포넌트

	// 총알 정보
	// BlueprintReadOnly 매개변수는 private에서 못쓴다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mag Info: Name")
		FName Mag_Name; // 탄창 이름
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mag Info: Type")
		int32 Mag_Type; // 1: 5.56 / 2: 7.62 / 3: 12gauge


};

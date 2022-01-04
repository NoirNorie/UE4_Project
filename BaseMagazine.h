// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// ĸ�� ������Ʈ ���
#include "Components/CapsuleComponent.h"
// ����ƽ �޽� ������Ʈ ���
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
		class UCapsuleComponent* Mag_Capsule; // �浹 ���� ������ ����� ĸ�� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mag_Mesh; // �޽� ǥ���� ����� ����ƽ �޽� ������Ʈ

	// �Ѿ� ����
	// BlueprintReadOnly �Ű������� private���� ������.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mag Info: Name")
		FName Mag_Name; // źâ �̸�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mag Info: Type")
		int32 Mag_Type; // 1: 5.56 / 2: 7.62 / 3: 12gauge


};

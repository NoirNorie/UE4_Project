// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


// ������ �����Լ� ���
#include "UObject/ConstructorHelpers.h"
// ĸ�� ������Ʈ ���
#include "Components/CapsuleComponent.h"
// ����ƽ �޽� ������Ʈ ���
#include "Components/StaticMeshComponent.h"
// ���̷�Ż �޽� ������Ʈ ���
#include "Components/SkeletalMeshComponent.h"

#include "TPlayer.h"
#include "TPlayerInterface.h"

#include "WeaponBase.generated.h"

// ���� ������ ���̽� Ŭ����

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
		class UCapsuleComponent* W_Contact; // �浹 ���� ������ ����� ĸ�� ������Ʈ
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	//	class UStaticMeshComponent* W_Mesh; // �޽� ǥ���� ����� ����ƽ �޽� ������Ʈ
	// ���� ���̷�Ż �޽÷� ǥ�� �����ؼ� �߰���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* SK_Mesh; // �޽� ǥ���� ����� ���̷�Ż �޽� ������Ʈ

	// �Ѿ� ����
	// BlueprintReadOnly �Ű������� private���� ������.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Info: Name")
		FName Weapon_Name; // ���� �̸�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Info: Ammo")
		int32 W_Ammo; // ���� �Ѿ�
	UPROPERTY(VIsibleAnywhere, BlueprintReadOnly, Category = "Weapon Info: WeaponDamage")
		float W_Damage; // ���� ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Info: FireRate")
		float W_FireRate; // ������ �߻� �ӵ�

	//UFUNCTION()
	//	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	//		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	//		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
};

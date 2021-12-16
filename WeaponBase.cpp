// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	W_Contact = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WCapsule")); // ĸ�� ������Ʈ ����
	W_Contact->SetupAttachment(RootComponent); // ��Ʈ ������Ʈ�� �����Ѵ�.

	SK_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shape")); // ���̷�Ż �޽� ������Ʈ ����
	SK_Mesh->SetupAttachment(W_Contact); // ĸ�� ������Ʈ�� �����Ѵ�.
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
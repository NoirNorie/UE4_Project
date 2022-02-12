// Fill out your copyright notice in the Description page of Project Settings.


#include "RootingBoxBase.h"

// Sets default values
ARootingBoxBase::ARootingBoxBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 콜리전
	RootingBoxCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootingBoxCollision->SetupAttachment(RootComponent);
	// 메시
	ST_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shape"));
	ST_Mesh->SetupAttachment(RootingBoxCollision);
	
	// 위젯
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(RootingBoxCollision);
	InteractionWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	InteractionWidget

}

// Called when the game starts or when spawned
void ARootingBoxBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARootingBoxBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


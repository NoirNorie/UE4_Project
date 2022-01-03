// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(1.0f);
	RootComponent = CollisionComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 20000.0f;
	ProjectileMovementComponent->MaxSpeed = 20000.0f;

	Damage = 20.0f;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	//CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnBeginOverlap);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseProjectile::OnEndOverlap);
}

void ABaseProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogClass, Warning, TEXT("ApplyDamage"));
	//FHitResult hitResult(ForceInit);
	//ABaseProjectile* hitBase = Cast<ABaseProjectile>(hitResult.Actor);

	//if (hitBase != nullptr)
	//{
	//	FPointDamageEvent damageEvent;
	//	damageEvent.HitInfo = hitResult;
	//	hitBase->TakeDamage(Damage, damageEvent, GetInstigatorController(), this);
	//}

	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;

	UGameplayStatics::ApplyDamage(OtherActor, 20.0f, NULL, GetOwner(), NULL);

}

void ABaseProjectile::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}
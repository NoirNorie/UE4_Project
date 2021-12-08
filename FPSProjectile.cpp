// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

		// Set the sphere's collision profile name to "Projectile".
		// ��ü �浹 ������ �̸��� ������
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		// ������ ���� ƨ��� �ȴ�

		// Event called when component hits something.
		// ������Ʈ�� ���𰡿� �浹�ϸ� �̺�Ʈ�� ȣ���Ѵ�
		CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
		// ������ ���� �浹�ϸ� ������� �ȴ�

		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		// ���۷��� ����� ����ü�� ��ġ�� �ܾ�´�
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/FirstPerson/Meshes/FirstPersonProjectileMesh.FirstPersonProjectileMesh'"));	
		// ����ü ����
		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}
		
		// �����ϰ� ���۷��� ����� ����ü ���͸����� ��ġ�� �ܾ�´�
		// ���۷��� ����� �ܾ�Դµ��� ���� �� �����Ϳ��� ������ ��ٸ� ���ٰ� �ٽ� �Ѻ���
		// �ٽ� Ų �� ���۷��� ����� �ٽ� �ܾ�ͼ� �ٿ��ֱ� �ϸ� �ߵȴ�.
		// �ٸ� ������δ� ���۷��� ��ΰ� �����¾Ƽ� �д� �Ϳ� ������ ���� ���ϼ��� �ִ�
		// ��θ� �����ص� �ߵȴ�.
		static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("MaterialInstanceConstant'/Game/Blueprints/SphereMat.SphereMat'"));
		// ����ü ���͸��� ����
		if (Material.Succeeded())
		{
			ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
		}
		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}

	// ��������� ������
	// - ����ü�� ������ �����Ѵ�
	// - ����ü�� ���� �մ´�
	// = ����ü�� ������ �����

	// Delete the projectile after 3 seconds.
	InitialLifeSpan = 3.0f;
	// �׽�Ʈ ���� ũ�Ⱑ ���Ƽ� Ȯ���� �ȵ�
	// = ���� �ƿ����̳ʿ��� ���� ����ü�� �����

	// ����ü�� �浹 ������ �𸮾� ������ �浹 ���ÿ��� �����Ѵ�
	// - ������Ʈ ���ÿ� ����


}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function that initializes the projectile's velocity in the shoot direction.
// ����ü�� �ʱ� �ӵ��� �߻� ������ �ʱ�ȭ�ϴ� �Լ� ����
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

// Function that is called when the projectile hits something.
// ����ü�� �浹�ߴٴ� ������ ������ �ı��ϴ� �ͱ��� �����Ѵ�.
void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}

	Destroy();
}
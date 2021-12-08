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
		// 구체 충돌 프로필 이름을 설정함
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		// 이제는 벽에 튕기게 된다

		// Event called when component hits something.
		// 컴포넌트가 무언가와 충돌하면 이벤트를 호출한다
		CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
		// 이제는 벽에 충돌하면 사라지게 된다

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
		// 레퍼런스 복사로 투사체의 위치를 긁어온다
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/FirstPerson/Meshes/FirstPersonProjectileMesh.FirstPersonProjectileMesh'"));	
		// 투사체 구현
		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}
		
		// 동일하게 레퍼런스 복사로 투사체 메터리얼의 위치를 긁어온다
		// 레퍼런스 복사로 긁어왔는데도 빌드 후 에디터에서 에러가 뜬다면 껏다가 다시 켜본다
		// 다시 킨 후 레퍼런스 복사로 다시 긁어와서 붙여넣기 하면 잘된다.
		// 다른 방법으로는 레퍼런스 경로가 지랄맞아서 읽는 것에 문제가 생긴 것일수도 있다
		// 경로를 단축해도 잘된다.
		static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("MaterialInstanceConstant'/Game/Blueprints/SphereMat.SphereMat'"));
		// 투사체 매터리얼 구현
		if (Material.Succeeded())
		{
			ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
		}
		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}

	// 현재까지의 문제점
	// - 투사체가 영원히 존재한다
	// - 투사체가 벽을 뚫는다
	// = 투사체의 수명을 만든다

	// Delete the projectile after 3 seconds.
	InitialLifeSpan = 3.0f;
	// 테스트 맵의 크기가 좁아서 확인이 안됨
	// = 월드 아웃라이너에서 보면 투사체가 사라짐

	// 투사체의 충돌 판정은 언리얼 엔진의 충돌 세팅에서 수행한다
	// - 프로젝트 세팅에 있음


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
// 투사체의 초기 속도와 발사 방향을 초기화하는 함수 구현
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

// Function that is called when the projectile hits something.
// 투사체가 충돌했다는 판정을 내리고 파괴하는 것까지 구현한다.
void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}

	Destroy();
}
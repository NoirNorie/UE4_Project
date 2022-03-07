// Fill out your copyright notice in the Description page of Project Settings.


#include "RootingBoxBase.h"
#include "TPlayer.h"
#include "UsableItemBase.h"
#include "DMRAmmo.h"
#include "Drink01.h"
#include "Drink02.h"
#include "Food01.h"
#include "Food02.h"
#include "HeavyAmmo.h"
#include "LightAmmo.h"

// Sets default values
ARootingBoxBase::ARootingBoxBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 콜리전
	RootingBoxCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootingBoxCollision->SetupAttachment(RootComponent);
	//RootingBoxCollision->AttachTo(RootComponent);
	// 메시
	ST_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shape"));
	ST_Mesh->SetupAttachment(RootingBoxCollision);
	//ST_Mesh->AttachTo(RootingBoxCollision);
	
	// 위젯
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(RootingBoxCollision);
	//InteractionWidget->AttachTo(RootingBoxCollision);
	InteractionWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	// 위젯 읽어오기
	static ConstructorHelpers::FClassFinder<UItemInteractionWidget>InterWidgetClass(TEXT
	("'/Game/Blueprint/Widget/InteractionWidget'"));
	
	if (InterWidgetClass.Succeeded())
	{
		InteractionWidget->SetWidgetClass(InterWidgetClass.Class);
		InteractionWidget->SetDrawSize(FVector2D(300.0f, 100.0f));
	}
	// 변수 초기화
	bOverlapped = false;
	bLooting = false;
	progressVar = 0.0f;

	Box_Name = "Item Box";

	// 드랍할 아이템을 맵에 기록해놓는다.
		// 소모 아이템
	//static ConstructorHelpers::FObjectFinder<UBlueprint>Food01(TEXT("/Game/Blueprint/Items/BP_Drink01"));
	static ConstructorHelpers::FClassFinder<ADrink01>Food01(TEXT("/Game/Blueprint/Items/BP_Drink01"));
	if (Food01.Succeeded() && Food01.Class != nullptr)
	{
		//TSubclassOf<class AActor> FoodItem1 = (UClass*)Food01.Object->GeneratedClass;
		TSubclassOf<class AActor> FoodItem1 = Food01.Class;
		ItemBPMap.Add(1, FoodItem1);
	}
	//static ConstructorHelpers::FObjectFinder<UBlueprint>Food02(TEXT("/Game/Blueprint/Items/BP_Drink02"));
	static ConstructorHelpers::FClassFinder<ADrink02>Food02(TEXT("/Game/Blueprint/Items/BP_Drink02"));
	if (Food02.Succeeded() && Food02.Class != nullptr)
	{
		//TSubclassOf<class AActor> FoodItem2 = (UClass*)Food02.Object->GeneratedClass;
		TSubclassOf<class AActor> FoodItem2 = Food02.Class;
		ItemBPMap.Add(2, FoodItem2);
	}
	//static ConstructorHelpers::FObjectFinder<UBlueprint>Food03(TEXT("/Game/Blueprint/Items/BP_Food01"));
	static ConstructorHelpers::FClassFinder<AFood01>Food03(TEXT("/Game/Blueprint/Items/BP_Food01"));
	if (Food03.Succeeded() && Food03.Class != nullptr)
	{
		//TSubclassOf<class AActor> FoodItem3 = (UClass*)Food03.Object->GeneratedClass;
		TSubclassOf<class AActor> FoodItem3 = Food03.Class;
		ItemBPMap.Add(3, FoodItem3);
	}
	//static ConstructorHelpers::FObjectFinder<UBlueprint>Food04(TEXT("/Game/Blueprint/Items/BP_Food02"));
	static ConstructorHelpers::FClassFinder<AFood02>Food04(TEXT("/Game/Blueprint/Items/BP_Food02"));
	if (Food04.Succeeded() && Food04.Class != nullptr)
	{
		// TSubclassOf<class AActor> FoodItem4 = (UClass*)Food04.Object->GeneratedClass;
		TSubclassOf<class AActor> FoodItem4 = Food04.Class;
		ItemBPMap.Add(4, FoodItem4);
	}
	// 총알 아이템
	//static ConstructorHelpers::FObjectFinder<UBlueprint>Ammo01(TEXT("/Game/Blueprint/Items/BP_HeavyAmmo"));
	static ConstructorHelpers::FClassFinder<AHeavyAmmo>Ammo01(TEXT("/Game/Blueprint/Items/BP_HeavyAmmo"));
	if (Ammo01.Succeeded() && Ammo01.Class != nullptr)
	{
		//TSubclassOf<class AActor> AmmoItem1 = (UClass*)Ammo01.Object->GeneratedClass;
		TSubclassOf<class AActor> AmmoItem1 = Ammo01.Class;
		ItemBPMap.Add(5, AmmoItem1);
	}
	//static ConstructorHelpers::FObjectFinder<UBlueprint>Ammo02(TEXT("/Game/Blueprint/Items/BP_LightAmmo"));
	static ConstructorHelpers::FClassFinder<ALightAmmo>Ammo02(TEXT("/Game/Blueprint/Items/BP_LightAmmo"));
	if (Ammo02.Succeeded())
	{
		//TSubclassOf<class AActor> AmmoItem2 = (UClass*)Ammo02.Object->GeneratedClass;
		TSubclassOf<class AActor> AmmoItem2 = Ammo02.Class;
		ItemBPMap.Add(6, AmmoItem2);
	}
	//static ConstructorHelpers::FObjectFinder<UBlueprint>Ammo03(TEXT("/Game/Blueprint/Items/BP_DMRAmmo"));
	static ConstructorHelpers::FClassFinder<ADMRAmmo>Ammo03(TEXT("/Game/Blueprint/Items/BP_DMRAmmo"));
	if (Ammo03.Succeeded())
	{
		//TSubclassOf<class AActor> AmmoItem3 = (UClass*)Ammo03.Object->GeneratedClass;
		TSubclassOf<class AActor> AmmoItem3 = Ammo03.Class;
		ItemBPMap.Add(7, AmmoItem3);
	}
}

// Called when the game starts or when spawned
void ARootingBoxBase::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add("ItemBox");

	// 위젯 연결
	auto tmpWidget = InteractionWidget->GetUserWidgetObject();
	DisplayedWidget = Cast<UItemInteractionWidget>(tmpWidget);
	if (DisplayedWidget)
	{
		DisplayedWidget->SetVisibility(ESlateVisibility::Collapsed);
		DisplayedWidget->SetItemName(Box_Name.ToString());
		DisplayedWidget->SetPercent(progressVar);
	}

	// 델리게이트 연결
	RootingBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ARootingBoxBase::OnBeginOverlap);
	RootingBoxCollision->OnComponentEndOverlap.AddDynamic(this, &ARootingBoxBase::OnEndOverlap);
	if (InfoPlayer != nullptr)
	{
		InfoPlayer->OnLootingStarted.BindUFunction(this, FName("CallDeleFunc_LootingStart"));
		InfoPlayer->OnLootingCancled.BindUFunction(this, FName("CallDeleFunc_LootingCancle"));
	}
	
}

// Called every frame
void ARootingBoxBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	if (bOverlapped == true && bLooting == true)
	{
		progressVar += 1.0f;
		DisplayedWidget->SetPercent(progressVar);
		if (progressVar >= 100.0f)
		{
			DropItem();
			Destroy();
		}
	}

}


void ARootingBoxBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->ActorHasTag(TEXT("Player")))
		{
			bOverlapped = true;
			if (DisplayedWidget)
			{
				if (!(DisplayedWidget->IsVisible()))
				{
					DisplayedWidget->SetVisibility(ESlateVisibility::Visible);
				}
			}
			TransferActor = OtherActor;

			InfoPlayer = Cast<ATPlayer>(TransferActor);
			if (InfoPlayer != nullptr)
			{
				InfoPlayer->OnLootingStarted.BindUFunction(this, FName("CallDeleFunc_LootingStart"));
				InfoPlayer->OnLootingCancled.BindUFunction(this, FName("CallDeleFunc_LootingCancle"));
			}
		}
	}
}

void ARootingBoxBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (DisplayedWidget)
	{
		DisplayedWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	bOverlapped = false;
	progressVar = 0.0f;
	TransferActor = nullptr;
	if (InfoPlayer != nullptr)
	{
		InfoPlayer->OnLootingStarted.Unbind();
		InfoPlayer->OnLootingCancled.Unbind();
	}
	InfoPlayer = nullptr;
}

void ARootingBoxBase::DropItem()
{
	int32 RandomNumb = FMath::RandRange(1, 10);
	if (RandomNumb <= 7) // 70%의 확률로 아이템을 드랍한다.
	{
		UWorld* world = GetWorld();
		if (world != nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("current Random Number %d"), RandomNumb));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			FRotator rotator;
			FVector SpawnLocation = GetActorLocation();
			world->SpawnActor<AActor>(*(ItemBPMap.Find(RandomNumb)), SpawnLocation, rotator, SpawnParams);
		}
	}
}

void ARootingBoxBase::CallDeleFunc_LootingStart()
{
	bLooting = true;
}

void ARootingBoxBase::CallDeleFunc_LootingCancle()
{
	bLooting = false;
	progressVar = 0.0f;
	if (DisplayedWidget)
	{
		DisplayedWidget->SetPercent(progressVar);
	}
}
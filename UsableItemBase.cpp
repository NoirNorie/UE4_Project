// Fill out your copyright notice in the Description page of Project Settings.


#include "UsableItemBase.h"

// Sets default values
AUsableItemBase::AUsableItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 콜리전 생성
	ItemCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WCapsule"));
	ItemCollision->SetupAttachment(RootComponent);
	// 메시 생성
	SK_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shape"));
	SK_Mesh->SetupAttachment(ItemCollision);
	// 위젯 컴포넌트 생성
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(ItemCollision);
	InteractionWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UItemInteractionWidget>ItemInterWidgetClass(TEXT
	("'/Game/Blueprint/Widget/InteractionWidget'"));
	if (ItemInterWidgetClass.Succeeded())
	{
		InteractionWidget->SetWidgetClass(ItemInterWidgetClass.Class);
		InteractionWidget->SetDrawSize(FVector2D(300.0f, 100.0f));
	}
	// 변수 초기화
	bOverlapped = false;
	bLooting = false;
	progressVar = 0.0f;

	Food_Name = "";
	fHungry = 0.0f;
	fThirsty = 0.0f;
}

// Called when the game starts or when spawned
void AUsableItemBase::BeginPlay()
{
	Super::BeginPlay();
	// 태그 연결
	Tags.Add("FoodItem");
	// 위젯 연결
	auto tmpWidget = InteractionWidget->GetUserWidgetObject();
	DisplayedWidget = Cast<UItemInteractionWidget>(tmpWidget);
	if (DisplayedWidget)
	{
		DisplayedWidget->SetVisibility(ESlateVisibility::Collapsed);
		DisplayedWidget->SetItemName(Food_Name.ToString());
		DisplayedWidget->SetPercent(progressVar);
	}
	// 델리게이트 연결
	ItemCollision->OnComponentBeginOverlap.AddDynamic(this, &AUsableItemBase::OnBeginOverlap);
	ItemCollision->OnComponentEndOverlap.AddDynamic(this, &AUsableItemBase::OnEndOverlap);
	if (InfoPlayer != nullptr)
	{
		InfoPlayer->OnLootingStarted.BindUFunction(this, FName("CallDeleFunc_LootingStart"));
		InfoPlayer->OnLootingCancled.BindUFunction(this, FName("CallDeleFunc_LootingCancle"));
	}

}

// Called every frame
void AUsableItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bOverlapped == true && bLooting == true)
	{
		progressVar += 1.0f;
		DisplayedWidget->SetPercent(progressVar);
		if (progressVar >= 100.0f)
		{
			GiveItem();
			Destroy();
		}
	}
}

void AUsableItemBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
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
void AUsableItemBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
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

void AUsableItemBase::GiveItem()
{
	if (TransferActor)
	{
		bool IsImplemented = TransferActor->GetClass()->ImplementsInterface(UTPlayerInterface::StaticClass());
		if (IsImplemented)
		{
			ITPlayerInterface* EQAmmoInterface = Cast<ITPlayerInterface>(TransferActor);
			if (EQAmmoInterface)
			{
				EQAmmoInterface->Execute_GetFoodItem(TransferActor, Food_Name, fHungry, fThirsty, FoodType);
			}
		}
	}
}

// 델리게이트 함수
void AUsableItemBase::CallDeleFunc_LootingStart()
{
	bLooting = true;
}
void AUsableItemBase::CallDeleFunc_LootingCancle()
{
	bLooting = false;
	progressVar = 0.0f;

	if (DisplayedWidget)
	{
		DisplayedWidget->SetPercent(progressVar);
	}
}
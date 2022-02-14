// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionDoorBase.h"

// Sets default values
AInteractionDoorBase::AInteractionDoorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DoorCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DoorCapsule"));
	DoorCollision->SetupAttachment(RootComponent);
	// 메시 생성
	ST_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shape"));
	ST_Mesh->SetupAttachment(DoorCollision);

	//ST_Mesh->SetupAttachment(DoorCollision);
	// 위젯 컴포넌트 생성
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(DoorCollision);
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
	bOpening = false;
	bDoorState = false;
	progressVar = 0.0f;

	rotator = 0.0f;

	DoorName = "";
	DoorLevel = 0;
}

// Called when the game starts or when spawned
void AInteractionDoorBase::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add("Door");
	// 위젯 연결
	auto tmpWidget = InteractionWidget->GetUserWidgetObject();
	DisplayedWidget = Cast<UItemInteractionWidget>(tmpWidget);
	if (DisplayedWidget)
	{
		DisplayedWidget->SetVisibility(ESlateVisibility::Collapsed);
		DisplayedWidget->SetItemName(DoorName.ToString());
		DisplayedWidget->SetPercent(progressVar);
	}
	// 델리게이트 연결
	DoorCollision->OnComponentBeginOverlap.AddDynamic(this, &AInteractionDoorBase::OnBeginOverlap);
	DoorCollision->OnComponentEndOverlap.AddDynamic(this, &AInteractionDoorBase::OnEndOverlap);
	if (InfoPlayer != nullptr)
	{
		InfoPlayer->OnLootingStarted.BindUFunction(this, FName("CallDeleFunc_LootingStart"));
		InfoPlayer->OnLootingCancled.BindUFunction(this, FName("CallDeleFunc_LootingCancle"));
	}
}

// Called every frame
void AInteractionDoorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bOverlapped == true && bOpening == true)
	{
		if (bDoorState != true)
		{
			progressVar += (0.5f / DoorLevel);
			DisplayedWidget->SetPercent(progressVar);
			if (progressVar >= 100.0f)
			{
				bDoorState = true;
				progressVar = 100.0f;
				DisplayedWidget->SetPercent(progressVar);
				OpenDoor();
			}
		}
	}
}

void AInteractionDoorBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
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
void AInteractionDoorBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
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

void AInteractionDoorBase::OpenDoor_Implementation()
{

}

void AInteractionDoorBase::CallDeleFunc_LootingStart()
{
	bOpening = true;
}

void AInteractionDoorBase::CallDeleFunc_LootingCancle()
{
	bOpening = false;
	if (!bDoorState)
	{
		progressVar = 0.0f;
		if (DisplayedWidget)
		{
			DisplayedWidget->SetPercent(progressVar);
		}
	}

}
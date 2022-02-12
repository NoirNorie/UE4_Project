// Fill out your copyright notice in the Description page of Project Settings.


#include "RootingBoxBase.h"
#include "TPlayer.h"

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

	Box_Name = "";
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
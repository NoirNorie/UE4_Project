// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	W_Contact = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WCapsule"));
	W_Contact->SetupAttachment(RootComponent);
	SK_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shape"));
	SK_Mesh->SetupAttachment(W_Contact);
	// 위젯이 표시될 곳을 만들어 놓는다.
	Inter_Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InterWidget"));
	Inter_Widget->SetupAttachment(W_Contact);
	Inter_Widget->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	Inter_Widget->SetWidgetSpace(EWidgetSpace::Screen); // 항상 플레이어를 향하도록 만든다.

	static ConstructorHelpers::FClassFinder<UItemInteractionWidget>ItemInterWidgetClass(TEXT
	("'/Game/Blueprint/Widget/InteractionWidget'"));

	if (ItemInterWidgetClass.Succeeded())
	{
		Inter_Widget->SetWidgetClass(ItemInterWidgetClass.Class);
		Inter_Widget->SetDrawSize(FVector2D(300.0f, 100.0f));
	}

	bOverlapped = false;
	bLooting = false;
	progressVar = 0.0f;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add("WeaponItem"); // 액터에 태그를 지정한다.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Load")));
	auto tmpWidget = Inter_Widget->GetUserWidgetObject(); // 위젯을 가져온다.
	DisplayedWidget = Cast<UItemInteractionWidget>(tmpWidget); // 타입을 변환한다.
	if (DisplayedWidget) // 된다면
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Widget Active")));
		DisplayedWidget->SetVisibility(ESlateVisibility::Collapsed); // 일단 안보이게 한다.

		// 위젯에 무기의 정보를 알린다.
		DisplayedWidget->SetItemName(Weapon_Name.ToString());
		DisplayedWidget->SetPercent(progressVar);
	}

	// 델리게이트 추가
	W_Contact->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnBeginOverlap);
	W_Contact->OnComponentEndOverlap.AddDynamic(this, &AWeaponBase::OnEndOverlap);

	if (InfoPlayer != nullptr)
	{
		InfoPlayer->OnLootingStarted.BindUFunction(this, FName("CallDeleFunc_LootingStart"));
		InfoPlayer->OnLootingCancled.BindUFunction(this, FName("CallDeleFunc_LootingCancle"));
	}


}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bOverlapped == true && bLooting == true) // 줍기 동작을 수행한다면 진행바를 증가시킨다.
	{
		progressVar += 0.5f;
		DisplayedWidget->SetPercent(progressVar);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Active %f"), progressVar));
		if (progressVar >= 100.0f)
		{
			GiveItem();
			Destroy();
		}
	}
}

void AWeaponBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->ActorHasTag(TEXT("Player"))) // 플레이어와만 상호작용을 하도록 만든다
		{
			bOverlapped = true; // 충돌 상태를 true로 바꾼다.

			if (DisplayedWidget)
			{
				if (!(DisplayedWidget->IsVisible())) // 안보인다면
				{
					// 위젯이 보이는지 안보이는지에 대한 구문이 없다면
					// overlap되는 순간 계속해서 보이도록 만들기 때문에 crash가 일어난다
					// 신기한 것은 ue4 crash report가 나타나지 않음
					// 아마도 틱마다 계속해서 위젯 상태를 변화시켜 자원 소모로 인해 나타나는 문제 같다.
					DisplayedWidget->SetVisibility(ESlateVisibility::Visible); // 위젯을 보이게 만든다
				}
			}
			TransferActor = OtherActor; // 액터 정보를 넘긴다.

			InfoPlayer = Cast<ATPlayer>(TransferActor);
			if (InfoPlayer != nullptr)
			{
				InfoPlayer->OnLootingStarted.BindUFunction(this, FName("CallDeleFunc_LootingStart"));
				InfoPlayer->OnLootingCancled.BindUFunction(this, FName("CallDeleFunc_LootingCancle"));
			}

			//bool IsImplemented = OtherActor->GetClass()->ImplementsInterface(UTPlayerInterface::StaticClass());
			//if (IsImplemented)
			//{
			//	ITPlayerInterface* EQWeaponInterface = Cast<ITPlayerInterface>(OtherActor);
			//	if (EQWeaponInterface)
			//	{
			//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Interface Active")));
			//		EQWeaponInterface->Execute_EquipWeaponItem(OtherActor, Weapon_Name, W_Ammo, W_Damage, W_FireRate, W_IDX);
			//	}
			//	// Destroy(); // 아이템을 획득할 경우 제거
			//}		
		}
	}
}

void AWeaponBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (DisplayedWidget)
	{
		DisplayedWidget->SetVisibility(ESlateVisibility::Collapsed); // 위젯을 안보이게 만든다.
	}
	bOverlapped = false;
	progressVar = 0.0f; // 진행도를 초기화한다.
	TransferActor = nullptr; // 액터 정보도 지운다.
	if (InfoPlayer != nullptr)
	{
		// 혹시 모를 메모리 누수를 방지하기 위해서 묶인 델리게이트를 해제한다.
		// 아직 발생한 경험은 없다.
		InfoPlayer->OnLootingStarted.Unbind();
		InfoPlayer->OnLootingCancled.Unbind();
	}
	InfoPlayer = nullptr;
}

void AWeaponBase::GiveItem()
{
	if (TransferActor)
	{
		bool IsImplemented = TransferActor->GetClass()->ImplementsInterface(UTPlayerInterface::StaticClass());
		if (IsImplemented)
		{
			ITPlayerInterface* EQWeaponInterface = Cast<ITPlayerInterface>(TransferActor);
			if (EQWeaponInterface)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Interface Active")));
				EQWeaponInterface->Execute_EquipWeaponItem(TransferActor, Weapon_Name, W_Ammo, W_Damage, W_FireRate, W_IDX);
			}
		}
	}
}

void AWeaponBase::CallDeleFunc_LootingStart()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Looting")));
	bLooting = true;
}
void AWeaponBase::CallDeleFunc_LootingCancle()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Looting Cancle")));
	bLooting = false;
	progressVar = 0.0f;
	
	if (DisplayedWidget)
	{
		DisplayedWidget->SetPercent(progressVar);
	}
}
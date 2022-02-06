// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryBase.h"

void UInventoryBase::NativeConstruct()
{
	Super::NativeConstruct();
	List = Cast<UListView>(GetWidgetFromName(TEXT("List")));
	currentIndex = 0;
	InventoryInit();
}

void UInventoryBase::InventoryInit()
{
	// 인벤토리 아이템을 등록해놓는다.
	// UInventoryData* HeavyAmmo = CreateDefaultSubobject<UInventoryData>(TEXT("HeavyAmmo"));
	UInventoryData* HeavyAmmo = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	//HeavyAmmo->SetItemIndex(0);
	HeavyAmmo->SetItemCount(0);
	HeavyAmmo->SetItemName("HeavyAmmo");
	HeavyAmmo->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Bullet03.Bullet03'"));
	List->AddItem(HeavyAmmo);
	
	UInventoryData* LightAmmo = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	//LightAmmo->SetItemIndex(1);
	LightAmmo->SetItemCount(0);
	LightAmmo->SetItemName("LightAmmo");
	LightAmmo->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Bullet04.Bullet04'"));
	List->AddItem(LightAmmo);

	UInventoryData* DMRAmmo = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	//DMRAmmo->SetItemIndex(2);
	DMRAmmo->SetItemCount(0);
	DMRAmmo->SetItemName("DMRAmmo");
	DMRAmmo->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/BulletBox.BulletBox'"));
	List->AddItem(DMRAmmo);

	UInventoryData* DMRAmmo2 = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	//DMRAmmo->SetItemIndex(2);
	DMRAmmo2->SetItemCount(0);
	DMRAmmo2->SetItemName("DMRAmmo");
	DMRAmmo2->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/BulletBox.BulletBox'"));
	List->AddItem(DMRAmmo2);
	DMRAmmo2 = nullptr;

	DMRAmmo2 = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	//DMRAmmo->SetItemIndex(2);
	DMRAmmo2->SetItemCount(0);
	DMRAmmo2->SetItemName("DMRAmmo");
	DMRAmmo2->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/BulletBox.BulletBox'"));
	List->AddItem(DMRAmmo2);
	DMRAmmo2 = nullptr;

	//UInventoryData* DMRAmmo = CreateDefaultSubobject<UInventoryData>(TEXT("DMRAmmo"));
	//HeavyAmmo->SetItemIndex(2);
	//HeavyAmmo->SetItemCount(0);
	//HeavyAmmo->SetItemName("DMRAmmo");
	//List->AddItem(DMRAmmo);
}

void UInventoryBase::ItemInsert(FName ItemName)
{
	//if (InventoryMap.Find(ItemName))
	//{
	//	int32* value = InventoryMap.Find(ItemName);
	//	value++;
	//}
	//else // 찾는 값이 없으면 Find함수가 nullptr을 반환한다 = 리스트에 값을 추가한다.
	//{
	//	InventoryMap.Add(ItemName, 1); // 맵에 값을 추가하여 기록한다.
	//	UInventoryData* ItemAdding = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	//	ItemAdding->SetItemCount(1);

	//}
}

void UInventoryBase::ItemDelete(FName ItemName)
{
	// List->RemoveItem();
}

void UInventoryBase::AmmoItemSelector(int32 t)
{
	UInventoryData* LootingAmmo = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	LootingAmmo->SetItemCount(1);
	if (LootingAmmo != nullptr)
	{
		switch (t)
		{
		case(0):
		{
			LootingAmmo->SetItemName("HeavyAmmo");
			LootingAmmo->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Bullet03.Bullet03'"));
		}
		case(1):
		{
			LootingAmmo->SetItemName("LightAmmo");
			LootingAmmo->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Bullet04.Bullet04'"));
		}
		case(2):
		{
			LootingAmmo->SetItemName("DMRAmmo");
			LootingAmmo->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/BulletBox.BulletBox'"));
		}
		}
		List->AddItem(LootingAmmo); // 아이템을 리스트 뷰 상에 추가한다.
		LootingAmmo = nullptr;		// nullptr을 가리키게 만든다. 
	}
}

void UInventoryBase::FoodItemSelector(int32 t)
{
	UInventoryData* LootingFood = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	LootingFood->SetItemCount(1);
	if (LootingFood != nullptr)
	{
		switch (t)
		{
		case(0):
		{
			LootingFood->SetItemName("Water");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Drink0.Drink0'"));
		}
		case(1):
		{
			LootingFood->SetItemName("Coke");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Drink1.Drink1'"));
		}
		case(2):
		{
			LootingFood->SetItemName("Milk");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Drink3.Drink3'"));
		}
		case(3):
		{
			LootingFood->SetItemName("FoodCan");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Food0.Food0'"));
		}
		case(4):
		{
			LootingFood->SetItemName("SoupCan");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Food3.Food3'"));
		}
		case(5):
		{
			LootingFood->SetItemName("Bread");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Food2.Food2'"));
		}
		case(6):
		{
			LootingFood->SetItemName("TunaCan");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Food4.Food4'"));
		}
		}
		List->AddItem(LootingFood);
		LootingFood = nullptr;
	}
}
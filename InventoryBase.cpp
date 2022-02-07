// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryBase.h"

void UInventoryBase::NativeConstruct()
{
	Super::NativeConstruct();
	List = Cast<UListView>(GetWidgetFromName(TEXT("List")));
	// InventoryInit();
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
	List->RemoveItem(HeavyAmmo); // 리스트 내부의 아이템 삭제
	
	UInventoryData* LightAmmo = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	//LightAmmo->SetItemIndex(1);
	LightAmmo->SetItemCount(0);
	LightAmmo->SetItemName("LightAmmo");
	LightAmmo->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Bullet04.Bullet04'"));
	List->AddItem(LightAmmo);
	List->RemoveItem(LightAmmo);

	UInventoryData* DMRAmmo = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	//DMRAmmo->SetItemIndex(2);
	DMRAmmo->SetItemCount(0);
	DMRAmmo->SetItemName("DMRAmmo");
	DMRAmmo->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/BulletBox.BulletBox'"));
	List->AddItem(DMRAmmo);
	List->RemoveItem(DMRAmmo);

	//UInventoryData* DMRAmmo = CreateDefaultSubobject<UInventoryData>(TEXT("DMRAmmo"));
	//HeavyAmmo->SetItemIndex(2);
	//HeavyAmmo->SetItemCount(0);
	//HeavyAmmo->SetItemName("DMRAmmo");
	//List->AddItem(DMRAmmo);
}

void UInventoryBase::ItemInsert(FName ItemName)
{

}

void UInventoryBase::ItemDelete(FName ItemName)
{
	// List->RemoveItem();
}

void UInventoryBase::AmmoInserter(FName AmmoName, int32 AmmoType)
{
	if (InventorySet.Find(AmmoName) != nullptr) // 찾는 총알이 있다면
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Already Exist Ammo")));

		// List->GetIndexForItem();

		// 아이템이 존재하는 사실이 확실하므로
		for (int i = 0; i < List->GetNumItems(); i++) // 어디에 있는지 찾아낸다.
		{
			UInventoryData* Data = Cast<UInventoryData>(List->GetItemAt(i)); // 인벤토리 내부에 있을 데이터를 구해온다.
			if (Data != nullptr && Data->GetItemName() == AmmoName.ToString())
			{
				Data->SetItemCount(Data->GetItemCount() + 1); // 개수를 하나 증가시킨다.
				break; // 불필요한 연산은 줄인다.
			}
		}
	}
	else // 찾는 총알이 없다면
	{
		InventorySet.Add(AmmoName); // 총알이 들어왔다는 사실을 기록한다.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("No Exist Ammo")));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Insert Sequence")));
		AmmoItemSelector(AmmoType); // 총알 아이템을 리스트에 추가하는 함수로 넘어간다.
	}

	if (List != nullptr) // 인벤토리를 갱신하여 변경 사항을 등록한다.
	{
		List->RegenerateAllEntries();
	}

}

void UInventoryBase::AmmoItemSelector(int32 t)
{
	UInventoryData* LootingAmmo = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	LootingAmmo->SetItemCount(1);
	if (LootingAmmo != nullptr)
	{
		switch (t)
		{
		case(1):
		{			
			LootingAmmo->SetItemIndex(1);
			LootingAmmo->SetItemName("LightAmmo");
			LootingAmmo->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Bullet04.Bullet04'"));
			break;
		}
		case(2):
		{
			LootingAmmo->SetItemIndex(2);
			LootingAmmo->SetItemName("HeavyAmmo");
			LootingAmmo->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Bullet03.Bullet03'"));
			break;
		}
		case(3):
		{
			LootingAmmo->SetItemIndex(3);
			LootingAmmo->SetItemName("DMRAmmo");
			LootingAmmo->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/BulletBox.BulletBox'"));
			break;
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
			LootingFood->SetItemIndex(4);
			LootingFood->SetItemName("Water");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Drink0.Drink0'"));
			break;
		}
		case(1):
		{
			LootingFood->SetItemIndex(5);
			LootingFood->SetItemName("Coke");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Drink1.Drink1'"));
			break;
		}
		case(2):
		{
			LootingFood->SetItemIndex(6);
			LootingFood->SetItemName("Milk");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Drink3.Drink3'"));
			break;
		}
		case(3):
		{
			LootingFood->SetItemIndex(7);
			LootingFood->SetItemName("FoodCan");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Food0.Food0'"));
			break;
		}
		case(4):
		{
			LootingFood->SetItemIndex(8);
			LootingFood->SetItemName("SoupCan");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Food3.Food3'"));
			break;
		}
		case(5):
		{
			LootingFood->SetItemIndex(9);
			LootingFood->SetItemName("Bread");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Food2.Food2'"));
			break;
		}
		case(6):
		{
			LootingFood->SetItemIndex(10);
			LootingFood->SetItemName("TunaCan");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Food4.Food4'"));
			break;
		}
		}
		List->AddItem(LootingFood);
		LootingFood = nullptr;
	}
}
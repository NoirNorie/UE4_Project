// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryBase.h"
// 플레이어 헤더
#include "TPlayer.h"
#include "TPlayerController.h"

void UInventoryBase::NativeConstruct()
{
	Super::NativeConstruct();
	List = Cast<UListView>(GetWidgetFromName(TEXT("List")));
	List->OnItemClicked().AddUObject(this, &UInventoryBase::ItemClick);
	// InventoryInit();
}

void UInventoryBase::InventoryInit()
{
	// 인벤토리 테스트 용 함수
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
}

void UInventoryBase::ItemClick(UObject* items)
{
	UInventoryData* ItemData = Cast<UInventoryData>(items);
	if (ItemData != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Click")));
		int32 ItemIndex = ItemData->GetItemIndex();
		if (ItemIndex > 3) // 인덱스가 3 이상일때만 동작하면 된다.
		{
			// 플레이어를 가져온다.
			ATPlayerController* PlayerCont = Cast<ATPlayerController>(GetWorld()->GetFirstPlayerController());
			if (PlayerCont != nullptr)
			{
				ATPlayer* Player = Cast<ATPlayer>(PlayerCont->GetCharacter());
				if (Player != nullptr)
				{
					Player->UseItem(ItemIndex, ItemData->GetIncHP(), ItemData->GetDecHungry(), ItemData->GetDecThrist());
				}
			}
			ItemData->SetItemCount(ItemData->GetItemCount() - 1);
			if (ItemData->GetItemCount() <= 0)
			{
				List->RemoveItem(ItemData);
				InventorySet.Remove(FName(ItemData->GetItemName()));
			}
		}
	}

	if (List != nullptr) // 인벤토리를 갱신하여 변경 사항을 등록한다.
	{
		List->RegenerateAllEntries();
	}

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

void UInventoryBase::FoodInserter(FName FoodName, float hungry, float thirst, int32 FoodType)
{
	if (InventorySet.Find(FoodName) != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Already Exist Food")));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("%d"), FoodType));
		// 아이템이 존재하는 사실이 확실하므로
		for (int i = 0; i < List->GetNumItems(); i++) // 어디에 있는지 찾아낸다.
		{
			UInventoryData* Data = Cast<UInventoryData>(List->GetItemAt(i)); // 인벤토리 내부에 있을 데이터를 구해온다.
			if (Data != nullptr && Data->GetItemName() == FoodName.ToString())
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("%d"), i));
				Data->SetItemCount(Data->GetItemCount() + 1); // 개수를 하나 증가시킨다.
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("INC")));
				break; // 불필요한 연산은 줄인다.
			}
		}
	}
	else // 찾는 음식이 없다면
	{
		InventorySet.Add(FoodName);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("No Exist Food")));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Insert Sequence")));
		FoodItemSelector(FoodType, hungry, thirst);
	}

	if (List != nullptr) // 인벤토리를 갱신하여 변경 사항을 등록한다.
	{
		List->RegenerateAllEntries();
	}
}

// 인벤토리 내부에 동일한 아이템이 존재하지 않을 경우 아이템을 추가하는 함수

void UInventoryBase::AmmoItemSelector(int32 t)
{
	UInventoryData* LootingAmmo = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
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
		LootingAmmo->SetItemCount(1);
		List->AddItem(LootingAmmo); // 아이템을 리스트 뷰 상에 추가한다.
		LootingAmmo = nullptr;
		// nullptr로 포인터를 지워줘야 제대로 동작한다.
	}
}

void UInventoryBase::FoodItemSelector(int32 t, float hungry, float thirst)
{
	UInventoryData* LootingFood = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("%d"), t));
	if (LootingFood != nullptr)
	{
		switch (t)
		{
		case(4):
		{
			LootingFood->SetItemIndex(4);
			LootingFood->SetItemName("Water");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Drink0.Drink0'"));
			break;
		}
		case(5):
		{

			LootingFood->SetItemIndex(5);
			LootingFood->SetItemName("Black Soda");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Drink1.Drink1'"));
			break;
		}
		case(6):
		{
			LootingFood->SetItemIndex(6);
			LootingFood->SetItemName("FoodCan");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Food0.Food0'"));
			break;
		}
		case(7):
		{
			LootingFood->SetItemIndex(7);
			LootingFood->SetItemName("SoupCan");
			LootingFood->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Food3.Food3'"));
			break;
		}
		}

		LootingFood->SetItemCount(1);
		LootingFood->SetItemDecHungry(hungry);
		LootingFood->SetItemDecThrist(thirst);
		List->AddItem(LootingFood);

		LootingFood = nullptr;
	}
}

int32 UInventoryBase::HaveAmmo(FName AmmoName)
{
	if (InventorySet.Find(AmmoName) != nullptr) // 찾는 총알이 있다면
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Ammo Exist")));
		// 총알이 확실하게 존재하므로
		for (int i = 0; i < List->GetNumItems(); i++) // 어디에 있는지 찾아낸다.
		{
			UInventoryData* Data = Cast<UInventoryData>(List->GetItemAt(i)); // 인벤토리 내부에 있을 데이터를 구해온다.
			if (Data != nullptr && Data->GetItemName() == AmmoName.ToString())
			{
				return Data->GetItemCount(); // 가지고 있는 총알 수를 반환한다.
			}
		}

		// 제어 경로 문제로 반환값을 설정한다
		// 여기까지 오면 뭔가 문제가 있는 것임
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Error Sequence")));
		return 0;
	}
	else
	{
		// 가지고 있는 총알이 없는 경우
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("No Exist")));
		return 0;
	}
}

void UInventoryBase::ReloadAmmo(FName AmmoName) // 재장전 동작
{
	if (InventorySet.Find(AmmoName) != nullptr) // 찾는 총알이 있다면
	{
		// 총알이 확실하게 존재하므로
		for (int i = 0; i < List->GetNumItems(); i++) // 어디에 있는지 찾아낸다.
		{
			UInventoryData* Data = Cast<UInventoryData>(List->GetItemAt(i)); // 인벤토리 내부에 있을 데이터를 구해온다.
			if (Data != nullptr && Data->GetItemName() == AmmoName.ToString())
			{
				Data->SetItemCount((Data->GetItemCount() - 1));
				if (Data->GetItemCount() <= 0)
				{
					List->RemoveItem(Data);
					InventorySet.Remove(AmmoName);
					//List->RegenerateAllEntries();
				}
				break;
			}
		}
	}

	if (List != nullptr) // 인벤토리를 갱신하여 변경 사항을 등록한다.
	{
		List->RegenerateAllEntries();
	}

}
// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryBase.h"

void UInventoryBase::NativeConstruct()
{
	Super::NativeConstruct();
	List = Cast<UListView>(GetWidgetFromName(TEXT("List")));
	InventoryInit();
}

void UInventoryBase::InventoryInit()
{
	// 인벤토리 아이템을 등록해놓는다.
	// UInventoryData* HeavyAmmo = CreateDefaultSubobject<UInventoryData>(TEXT("HeavyAmmo"));
	UInventoryData* HeavyAmmo = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	HeavyAmmo->SetItemIndex(0);
	HeavyAmmo->SetItemCount(0);
	HeavyAmmo->SetItemName("HeavyAmmo");
	HeavyAmmo->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Bullet03.Bullet03'"));
	List->AddItem(HeavyAmmo);
	

	UInventoryData* LightAmmo = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	LightAmmo->SetItemIndex(1);
	LightAmmo->SetItemCount(0);
	LightAmmo->SetItemName("LightAmmo");
	LightAmmo->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/Bullet04.Bullet04'"));
	List->AddItem(LightAmmo);

	UInventoryData* DMRAmmo = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	DMRAmmo->SetItemIndex(2);
	DMRAmmo->SetItemCount(0);
	DMRAmmo->SetItemName("DMRAmmo");
	DMRAmmo->SetItemIcon(TEXT("Texture2D'/Game/Blueprint/ETC/BulletBox.BulletBox'"));
	List->AddItem(DMRAmmo);

	//UInventoryData* DMRAmmo = CreateDefaultSubobject<UInventoryData>(TEXT("DMRAmmo"));
	//HeavyAmmo->SetItemIndex(2);
	//HeavyAmmo->SetItemCount(0);
	//HeavyAmmo->SetItemName("DMRAmmo");
	//List->AddItem(DMRAmmo);
}
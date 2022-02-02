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
	List->AddItem(LightAmmo);

	//UInventoryData* DMRAmmo = NewObject<UInventoryData>(this, UInventoryData::StaticClass());
	//HeavyAmmo->SetItemIndex(2);
	//HeavyAmmo->SetItemCount(0);
	//HeavyAmmo->SetItemName("DMRAmmo");
	//List->AddItem(DMRAmmo);

	//UInventoryData* DMRAmmo = CreateDefaultSubobject<UInventoryData>(TEXT("DMRAmmo"));
	//HeavyAmmo->SetItemIndex(2);
	//HeavyAmmo->SetItemCount(0);
	//HeavyAmmo->SetItemName("DMRAmmo");
	//List->AddItem(DMRAmmo);
}
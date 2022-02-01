// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryBase.h"

UInventoryBase::UInventoryBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UInventoryBase::NativeConstruct()
{
	Super::NativeConstruct();

	List = Cast<UListView>(GetWidgetFromName(TEXT("List")));
	TArray<UInventoryData*>Inventory;
	List->SetListItems(InventoryItems);

	// InventoryInit();
	//List->AddItem(HeavyAmmo);
}

void UInventoryBase::InventoryInit()
{
	UInventoryData* HeavyAmmo = CreateDefaultSubobject<UInventoryData>(TEXT("HeavyAmmo"));
	HeavyAmmo->SetItemIndex(0);
	HeavyAmmo->SetItemCount(0);
	HeavyAmmo->SetItemName("HeavyAmmo");
	List->AddItem(HeavyAmmo);

	UInventoryData* LightAmmo = CreateDefaultSubobject<UInventoryData>(TEXT("LightAmmo"));
	HeavyAmmo->SetItemIndex(1);
	HeavyAmmo->SetItemCount(0);
	HeavyAmmo->SetItemName("LightAmmo");
	List->AddItem(LightAmmo);

	UInventoryData* DMRAmmo = CreateDefaultSubobject<UInventoryData>(TEXT("DMRAmmo"));
	HeavyAmmo->SetItemIndex(2);
	HeavyAmmo->SetItemCount(0);
	HeavyAmmo->SetItemName("DMRAmmo");
	List->AddItem(DMRAmmo);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryBase.h"

UInventoryBase::UInventoryBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UInventoryBase::NativeConstruct()
{
	Super::NativeConstruct();

	UInventoryData* HeavyAmmo = CreateDefaultSubobject<UInventoryData>(TEXT("HeavyAmmo"));
	HeavyAmmo->SetItemIndex(0);
	HeavyAmmo->SetItemCount(0);
	HeavyAmmo->SetItemName("HeavyAmmo");
	// HeavyAmmo->SetItemIcon(TEXT(""));

	List->AddItem(HeavyAmmo);

}
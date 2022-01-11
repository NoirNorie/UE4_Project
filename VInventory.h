// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VCustomUI.h"
#include "VInventory.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UVInventory : public UVCustomUI
{
	GENERATED_BODY()
public:
	UVInventory(const FObjectInitializer& ObjectInitializer);
	void Init() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* DefaultTex;
private:
	/*TArray<USlot*> Slots;*/
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VCustomUI.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "VSlot.generated.h"

/**
 * 
 */
UCLASS()
class PP_API UVSlot : public UVCustomUI
{
	GENERATED_BODY()
public:
	void Init() override;
	void setType(ESlotType type);
	void setTexture(UTexture2D* tex);
	void Refresh();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMax = 32, UIMin = -1))
		int SlotNum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int Count;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TEnumAsByte<ESlotType> Type;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* Img;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* Text;
	
};

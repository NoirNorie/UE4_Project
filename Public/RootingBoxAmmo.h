// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RootingBoxBase.h"
#include "RootingBoxAmmo.generated.h"

/**
 * 
 */
UCLASS()
class PP_API ARootingBoxAmmo : public ARootingBoxBase
{
	GENERATED_BODY()
public:
	ARootingBoxAmmo();
	void DropItem() override;
};

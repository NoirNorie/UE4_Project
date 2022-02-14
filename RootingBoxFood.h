// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RootingBoxBase.h"
#include "RootingBoxFood.generated.h"

/**
 * 
 */
UCLASS()
class PP_API ARootingBoxFood : public ARootingBoxBase
{
	GENERATED_BODY()
protected:
	void DropItem();
};

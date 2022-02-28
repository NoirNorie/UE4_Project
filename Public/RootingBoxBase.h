// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// 컴포넌트 헤더
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
// 아이템 상호작용 시 띄울 위젯 헤더
#include "ItemInteractionWidget.h"

#include "RootingBoxBase.generated.h"

UCLASS()
class PP_API ARootingBoxBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARootingBoxBase();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Casule", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* RootingBoxCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Casule", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ST_Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Casule", meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* InteractionWidget;
	UItemInteractionWidget* DisplayedWidget;

	// 플레이어와 충돌 액터의 정보를 담을 액터 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
		class ATPlayer* InfoPlayer;
	AActor* TransferActor;

	// 아이템 정보 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Usable Item Info")
		FName Box_Name;

	// 플래그 변수
	bool bOverlapped;
	bool bLooting;
	int32 FoodType;
	// 진행바 변수
	float progressVar;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> ItemBPs;

	// 아이템 처리용 맵
	TMap<int32, TSubclassOf<class AActor>> ItemBPMap;

	// 충돌 확인 함수
	UFUNCTION() void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void virtual DropItem();

	// 델리게이트 함수
	UFUNCTION() void CallDeleFunc_LootingStart();
	UFUNCTION() void CallDeleFunc_LootingCancle();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

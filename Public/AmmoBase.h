// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// 생성자 보조함수 헤더
#include "UObject/ConstructorHelpers.h"
// 컴포넌트 헤더
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
// 플레이어 헤더
#include "TPlayer.h"
#include "TPlayerInterface.h"
// 아이템 상호작용 시 띄울 위젯 헤더
#include "ItemInteractionWidget.h"

#include "AmmoBase.generated.h"

UCLASS()
class PP_API AAmmoBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoBase();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Casule", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* ItemCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Casule", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* SK_Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Casule", meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* InteractionWidget;
	UItemInteractionWidget* DisplayedWidget;

	// 플레이어와 충돌 액터의 정보를 담을 액터 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	class ATPlayer* InfoPlayer;
	AActor* TransferActor;

	// 아이템 정보 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AmmoInfo")
		FName Ammo_Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AmmoInfo")
		int32 Ammo_Type;

	// 플래그 변수
	bool bOverlapped;
	bool bLooting;
	// 진행바 변수
	float progressVar = 0.0f;

	// 충돌 확인 함수
	UFUNCTION() void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// 아이템을 전달할 함수
	UFUNCTION() void GiveItem();

	// 델리게이트 함수
	UFUNCTION() void CallDeleFunc_LootingStart();
	UFUNCTION() void CallDeleFunc_LootingCancle();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

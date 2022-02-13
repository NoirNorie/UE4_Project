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
// 플레이어 헤더
#include "TPlayer.h"
#include "TPlayerInterface.h"
// 아이템 상호작용 시 띄울 위젯 헤더
#include "ItemInteractionWidget.h"

#include "InteractionDoorBase.generated.h"

UCLASS()
class PP_API AInteractionDoorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionDoorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* DoorCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ST_Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule", meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* InteractionWidget;

	UItemInteractionWidget* DisplayedWidget;

	// 플레이어와 충돌 액터의 정보를 담을 액터 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
		class ATPlayer* InfoPlayer;
	AActor* TransferActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Info")
		FName DoorName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Info")
		int32 DoorLevel;

	// 플래그 변수
	bool bOverlapped;
	bool bOpening;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Info")
	bool bDoorState;
	// 진행바 변수
	float progressVar;
	// 회전 변수
	float rotator;

	UFUNCTION(BlueprintNativeEvent)
		void OpenDoor();

	// 충돌 확인 함수
	UFUNCTION() void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// 델리게이트 함수
	UFUNCTION() void CallDeleFunc_LootingStart();
	UFUNCTION() void CallDeleFunc_LootingCancle();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

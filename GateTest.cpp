// Fill out your copyright notice in the Description page of Project Settings.


#include "GateTest.h"

// Sets default values
AGateTest::AGateTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Curve1 = nullptr;
	Curve2 = nullptr;
	Curve3 = nullptr;
	LerpTimelineLength = 0.4f;

}

// Called when the game starts or when spawned
void AGateTest::BeginPlay()
{
	Super::BeginPlay();
	
	if (Curve1 != nullptr && Curve2 != nullptr && Curve3 != nullptr)
	{
		FOnTimelineFloat Curve1Callback;
		FOnTimelineVector Curve2Callback;
		FOnTimelineLinearColor Curve3Callback;

		FOnTimelineEventStatic LerpTimelineFinishedCallback;

		Curve1Callback.BindUFunction(this, FName("func1"));
		Curve2Callback.BindUFunction(this, FName("func2"));
		Curve3Callback.BindUFunction(this, FName("func3"));
		LerpTimelineFinishedCallback.BindUFunction(this, FName("func4"));

		// 타임라인에 커브와 커브를 사용할 콜백 함수 추가
		LerpTimeline.AddInterpFloat(Curve1, Curve1Callback);
		LerpTimeline.AddInterpVector(Curve2, Curve2Callback);
		LerpTimeline.AddInterpLinearColor(Curve3, Curve3Callback);
		// 타임라인이 끝날 때 호출할 콜백 함수를 추가
		LerpTimeline.SetTimelineFinishedFunc(LerpTimelineFinishedCallback);

		// 타임라인 길이 설정
		LerpTimeline.SetTimelineLength(LerpTimelineLength);
	}
	// 타임라인 실행
	LerpTimeline.PlayFromStart();
}

// Called every frame
void AGateTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LerpTimeline.TickTimeline(DeltaTime);
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "WeaponAR15.generated.h"

/**
 * 
 */
UCLASS()
class PP_API AWeaponAR15 : public AWeaponBase
{
	GENERATED_BODY()
public:
	// 생성자
	AWeaponAR15();

	// ue4에서 LNK1169와 LNK2005가 뜬다
	// 이 경우에는 로그를 보고 경로를 찾아간다
	// ex) 프로젝트명\Intermediate\Build\Win64\UE4Editor\Development\프로젝트명
	// 여기서 fatal error에 해당하는 파일들을 고른다
	// 또한 LNK1169는 기호 중복 에러에 해당하므로 다 처리되지 못한 cpp.obj 파일이 있다면 이것도 고른다
	// 혹시 모르니 다 복사해서 백업한 후 제거한다
	// 해결이 되면 백업은 남겨놓든 구워 삶든 한다
	// 해결이 안되면 되돌리고 다른 방법을 찾아본다 (이 방법으로 해결해서 아직 이 경우는 없었다)

	// ue4에서 가끔 디테일 패널이 열리지 않는 버그가 존재한다
	// 한국어로 된 설명이나 글이 없어서 영문 자료들을 조사해봤는데 해결방법이 나왔다
	// 0: UPROPERTY의 내용이 보이지 않게 설정되었는지 확인한다.
	// 1: 생성한 BP에 들어가서 부모 클래스를 변경한다(관련 없는 것으로)
	// 2: 부모 클래스를 다시 원래 의도했던 클래스로 변경한다. (대부분 여기서 된다)
	// 3: 그래도 디테일 패널이 열리지 않는다면
	// 4: BP를 지우고 다시 만든다
	
	// 비슷한 유형으로 컴포넌트들의 위치가 빗나가는 문제도 해결할 수 있었다.

};

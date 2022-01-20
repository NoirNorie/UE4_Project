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

	// 생성자
	AWeaponAR15();
public:

	// ue4에서 LNK1169와 LNK2005가 뜬다
	// 이 경우에는 로그를 보고 경로를 찾아간다
	// ex) 프로젝트명\Intermediate\Build\Win64\UE4Editor\Development\프로젝트명
	// 여기서 fatal error에 해당하는 파일들을 고른다
	// 또한 LNK1169는 기호 중복 에러에 해당하므로 다 처리되지 못한 cpp.obj 파일이 있다면 이것도 고른다
	// 혹시 모르니 다 복사해서 백업한 후 제거한다
	// 해결이 되면 백업은 남겨놓든 구워 삶든 한다
	// 해결이 안되면 되돌리고 다른 방법을 찾아본다 (이 방법으로 해결해서 아직 이 경우는 없었다)
};

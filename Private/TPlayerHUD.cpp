// Fill out your copyright notice in the Description page of Project Settings.


#include "TPlayerHUD.h"

//ATPlayerHUD::ATPlayerHUD()
//{
//	static ConstructorHelpers::FObjectFinder<UTexture2D>texture(TEXT("Texture2D'/Game/Blueprint/ETC/crosshair.crosshair'"));
//	if (texture.Succeeded()) CrossHair = texture.Object;
//}

void ATPlayerHUD::DrawHUD()
{
	Super::DrawHUD();

	if (CrossHair)
	{
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		FVector2D CrossHairDrawPosition(Center.X - (CrossHair->GetSurfaceWidth() * 0.5f), Center.Y - (CrossHair->GetSurfaceHeight() * 0.5f));


		FCanvasTileItem TileItem(CrossHairDrawPosition, CrossHair->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}
}
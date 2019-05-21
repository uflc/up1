// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibrary.h"
#include "PaperSprite.h"


FVector2D UMyBlueprintFunctionLibrary::GetSourceSize(UPaperSprite* sprite)
{
	UTexture2D* texture = sprite->GetBakedTexture();
	return texture ? FVector2D(texture->GetSizeX(), texture->GetSizeY()) : FVector2D();
}

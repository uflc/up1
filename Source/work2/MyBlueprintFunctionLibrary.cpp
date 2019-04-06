// Fill out your copyright notice in the Description page of Project Settings.

//#include "work2.h"
#include "MyBlueprintFunctionLibrary.h"

FVector2D UMyBlueprintFunctionLibrary::GetSourceSize(UPaperSprite* sprite)
{
	return sprite->GetSourceSize();

}


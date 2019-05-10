// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibrary.h"
//#include "work2.h"


FVector2D UMyBlueprintFunctionLibrary::GetSourceSize(UPaperSprite* sprite)
{
	UTexture2D* texture = sprite->GetBakedTexture();
	return texture ? FVector2D(texture->GetSizeX(), texture->GetSizeY()) : FVector2D();
}

FORCEINLINE void UMyBlueprintFunctionLibrary::EarnCoin(UObject * CalledObj, int32 Value)
{
	UGameplayStatics::GetPlayerController(CalledObj->GetWorld(), 0)->GetPlayerState<ATDPlayerStateBase>()->UpdateValue(Value, EValueType::Coin);
}

FORCEINLINE void UMyBlueprintFunctionLibrary::UpdateCurrentPlayerStateValue(UObject * CalledObj, int32 Value, EValueType Type)
{
	UGameplayStatics::GetPlayerController(CalledObj->GetWorld(), 0)->GetPlayerState<ATDPlayerStateBase>()->UpdateValue(Value, Type);
}

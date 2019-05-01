// Fill out your copyright notice in the Description page of Project Settings.

//#include "work2.h"
#include "MyBlueprintFunctionLibrary.h"


FORCEINLINE FVector2D UMyBlueprintFunctionLibrary::GetSourceSize(UPaperSprite* sprite)
{
	return sprite->GetSourceSize();
}

FORCEINLINE void UMyBlueprintFunctionLibrary::EarnCoin(UObject * CalledObj, int32 Value)
{
	UGameplayStatics::GetPlayerController(CalledObj->GetWorld(), 0)->GetPlayerState<ATDPlayerStateBase>()->UpdateValue(Value, EValueType::Coin);
}

FORCEINLINE void UMyBlueprintFunctionLibrary::UpdateCurrentPlayerStateValue(UObject * CalledObj, int32 Value, EValueType Type)
{
	UGameplayStatics::GetPlayerController(CalledObj->GetWorld(), 0)->GetPlayerState<ATDPlayerStateBase>()->UpdateValue(Value, Type);
}

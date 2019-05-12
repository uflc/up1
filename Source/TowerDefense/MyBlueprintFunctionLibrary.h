// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDPlayerStateBase.h"
#include "PaperSprite.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 BP에 커스텀으로 추가하기 위한 라이브러리.
 */
UCLASS()
class TOWERDEFENSE_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	//스프라이트의 텍스쳐 디멘션.
	UFUNCTION(BlueprintPure, Category = Custom)
	static FVector2D GetSourceSize(UPaperSprite* sprite);

	UFUNCTION(BlueprintCallable, Category = Custom)
	static void EarnCoin(UObject* CalledObj,int32 Value);

	UFUNCTION(BlueprintCallable, Category = Custom) 
	static void UpdateCurrentPlayerStateValue(UObject* CalledObj, int32 i,EValueType Type);
};

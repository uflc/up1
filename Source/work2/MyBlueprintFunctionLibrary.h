// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PaperSprite.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class WORK2_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
		UFUNCTION(BlueprintPure, Category = Custom) //Here you can change the keywords, name and category
		static FVector2D GetSourceSize(UPaperSprite* sprite);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelDataBase.generated.h"


class AMyPaperCharacter;
class UMyPaperCharacterCommon;
/**
 * 
 */
UCLASS(BluePrintable)
class WORK2_API ULevelDataBase : public UObject
{
	GENERATED_BODY()
	
protected:
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	TMap<TSubclassOf<AMyPaperCharacter>, TSubclassOf<UMyPaperCharacterCommon>> UnitDataMap;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FVector Destination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 DefaultCoin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 DefaultLife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 DefaultMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 DefaultHeroHP;
};

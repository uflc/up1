// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveData.h"
#include "LevelData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TOWERDEFENSE_API ULevelData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DefaultCoin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DefaultLife;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DefaultMana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DefaultHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName NextLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector HeroSpawnLocation;
};

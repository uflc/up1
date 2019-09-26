// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/TowerDataTree.h"
#include "ProfTowerData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTalentInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<int32> Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Preview;
};

UCLASS(BlueprintType)
class TOWERDEFENSE_API UProfTowerData : public UTowerData
{
	GENERATED_BODY()
	
protected:
	FTalentInfo Talents[UPGRADES_NUM];

};

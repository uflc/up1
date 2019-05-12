// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "TowerBarracks.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerBarracks : public ATower
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATowerBarracks();

protected:
	static TMap<ETowerState, TArray<TSoftObjectPtr<UPaperFlipbook>>> FlipbookMap;

	static int8 MaxUnitNumber;

public:
	virtual FString GetPresetName();

	virtual FString GetTowerStatusText();

	virtual FString GetTowerDescriptionText();

	virtual float GetTowerRange() override;

	virtual TSoftObjectPtr<UPaperFlipbook> GetFlipbookOfCurrentState();
};
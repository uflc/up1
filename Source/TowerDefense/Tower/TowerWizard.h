// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "TowerWizard.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerWizard : public ATower
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ATowerWizard();

protected:

	static TMap<uint8, float> TowerAttackRangeMap;
	static TMap<uint8, float> TowerAttackSpeedMap;
	static TMap<uint8, int32> TowerAttackDmgMap;

	static TMap<ETowerState, TArray<TSoftObjectPtr<UPaperFlipbook>>> FlipbookMap;

public:
	virtual FString GetPresetName();
	virtual FString GetTowerStatusText();
	virtual FString GetTowerDescriptionText();

	virtual float GetTowerRange() override;
	virtual float GetTowerAttackSpd() override;
	virtual int32 GetTowerAttackDmg() override;

	virtual TSoftObjectPtr<UPaperFlipbook> GetFlipbookOfCurrentState();
};

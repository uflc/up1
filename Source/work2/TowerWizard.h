// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "TowerWizard.generated.h"

/**
 * 
 */
UCLASS()
class WORK2_API ATowerWizard : public ATower
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ATowerWizard();

protected:

	static float TowerAttackRange;
	static float TowerAttackSpeed;
	static float TowerAttackDmg;
	static TMap<ETowerState, TArray<TSoftObjectPtr<UPaperFlipbook>>> FlipbookMap;

public:
	virtual FString GetPresetName();
	virtual FString GetTowerStatusText();
	virtual FString GetTowerDescriptionText();

	virtual float GetTowerRange();
	virtual float GetTowerAttackSpd();
	virtual float GetTowerAttackDmg();

	virtual TSoftObjectPtr<UPaperFlipbook> GetFlipbookOfCurrentState();
};

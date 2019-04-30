// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "TowerArcher.generated.h"

/**
 * 
 */
UCLASS()
class WORK2_API ATowerArcher : public ATower
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATowerArcher();
protected:

	static float TowerAttackRange;
	static float TowerAttackSpeed;
	static int32 TowerAttackDmg;
	static TMap<ETowerState, TArray<TSoftObjectPtr<UPaperFlipbook>>> FlipbookMap;

public:
	virtual FString GetPresetName();
	virtual FString GetTowerStatusText();
	virtual FString GetTowerDescriptionText();

	virtual float GetTowerRange();
	virtual float GetTowerAttackSpd();
	virtual int32 GetTowerAttackDmg();

	virtual TSoftObjectPtr<UPaperFlipbook> GetFlipbookOfCurrentState();
};

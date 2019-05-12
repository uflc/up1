// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "TowerEmpty.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerEmpty : public ATower
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATowerEmpty();

protected:

public:
	virtual FString GetPresetName();

	virtual FString GetTowerStatusText();

	virtual FString GetTowerDescriptionText();

};

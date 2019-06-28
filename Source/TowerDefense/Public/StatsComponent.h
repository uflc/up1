// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TDComponent.h"
#include "StatsComponent.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UStatsComponent : public UTDComponent
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
	int32 HP;


public;
	UFUNCTION()
	void TakeDamage(const FDamage& InDamage);
};

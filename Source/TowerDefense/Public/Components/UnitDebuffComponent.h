// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "Components/TDComponent.h"
#include "TDTypes.h"
#include "UnitDebuffComponent.generated.h"

/**
 * 
 */

UCLASS()
class TOWERDEFENSE_API UUnitDebuffComponent : public UTDComponent
{
	GENERATED_BODY()
	
protected:	
	TMultiMap<EDebuffType,FDebuff> DebuffMap;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<int,FTimerHandle> TimerMap;

public:
	UFUNCTION()
	void RegDebuff(const FDebuff& Debuff);

	UFUNCTION()
	void UnregDebuff(FDebuff & Debuff);

	UFUNCTION()
	void UpdateStat(const FDebuff& InDebuff, bool bDebuffStart); // Broadcast?

	bool IsDebuffTypeOverlappable(const EDebuffType& InDebuffType);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TDComponent.h"
#include "TDTypes.h"
#include "UnitDebuffComponent.generated.h"

/*
 * MulMod는 %로 곱연산.
 * AddMod는 값으로 합연산.
 */
USTRUCT()
struct FBuffModifier
{
	GENERATED_BODY()

	//Base value which will be modified.
	float BaseVal = 0.0f;

	//Primary Modifers directly modify BaseMod.
	float PriMulMod = 1.0f;
	float PriAddMod = 0.0f;

	//Secondary Modifers are applied after primary modification.
	float SecMulMod = 1.0f;
	float SecAddMod = 0.0f;

	float CalcModifier() const
	{
		return (BaseVal * PriMulMod + PriAddMod) * SecMulMod + SecAddMod;
	}

	float SetModifier(const bool bIsAdditive, const bool bIsPositive, float Power)
	{
		if (bIsAdditive)
		{
			PriAddMod += bIsPositive ? Power : -Power;
		}
		else
		{
			float PowerAsPercent = (1 - (Power / 100));
			PriMulMod *= bIsPositive ? PowerAsPercent : 1/PowerAsPercent;
		}
		return CalcModifier();
	}
};

/**
 * 
 */

UCLASS()
class TOWERDEFENSE_API UUnitDebuffComponent : public UTDComponent
{
	GENERATED_BODY()
	
protected:
	TMultiMap<EDebuffType, FDebuff> BuffTypeDataMap;

	UPROPERTY()
	TMap<EDebuffType, FBuffModifier> BuffTypeModMap;

	TMap<int, TArray<FTimerHandle>> BuffIDTimersMap;

	bool bIsStopped;

public:
	UFUNCTION()
	void RegDebuff(const FDebuff& Debuff);

	UFUNCTION()
	void UnregDebuff(FDebuff & Debuff);

	UFUNCTION()
	void UpdateStat(const FDebuff& InDebuff, bool bDebuffStart); // Broadcast?

	bool IsBlendable(const EDebuffType& InDebuffType);
};

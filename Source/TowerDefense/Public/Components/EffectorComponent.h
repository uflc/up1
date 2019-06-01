// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDComponent.h"
#include "TDTypes.h"
#include "EffectorComponent.generated.h"

/**
 * 
 */
 class ATDCharacter;
UCLASS(Blueprintable, Abstract, ClassGroup = (Custom))
class TOWERDEFENSE_API UEffectorComponent : public UTDComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	uint32 Damage;

	UPROPERTY()
	float EffectRange;

	UPROPERTY()
	TArray<FDebuff> Debuffs;

	//todo some useful vars for fun like DamageIncreaseRate, Stack, Timer, etc...
public:
	virtual void InflictEffect(ATDCharacter* Target);

	//todo DebuffSet... DataAsset or Structure or Archetype
	void Initialize(float InEffectRange, uint32 InDamage);

	UFUNCTION(BlueprintCallable)
	virtual void InflictAoE(ATDCharacter* MainTarget);
};

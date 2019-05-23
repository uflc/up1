// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectorComponent.h"
#include "DamagerComponent.generated.h"

/**
 * 
 */
 class ATDCharacter;
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UDamagerComponent : public UEffectorComponent
{
	GENERATED_BODY()
	
	UDamagerComponent();

public:
	int Damage;

public:
	virtual void Effect(ATDCharacter* Target) override;
	void InitializeDamagerComp(float iEffectRange, int iDamage);
};

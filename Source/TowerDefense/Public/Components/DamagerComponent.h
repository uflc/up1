// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectorComponent.h"
#include "DamagerComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UDamagerComponent : public UEffectorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage;

public:
	virtual void Effect(class ATDCharacter* Target) override;
	void InitializeDamagerComp(float InEffectRange, int InDamage);
};

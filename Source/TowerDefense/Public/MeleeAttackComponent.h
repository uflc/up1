// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "MeleeAttackComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UMeleeAttackComponent : public UAttackComponent
{
	GENERATED_BODY()

public:
	virtual void ExecAttack(class UObject* Target) override;
};

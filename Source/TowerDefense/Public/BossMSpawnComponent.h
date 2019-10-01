// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WeaponComponent.h"
#include "BossMSpawnComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API UBossMSpawnComponent : public UWeaponComponent
{
	GENERATED_BODY()
	
public:
	virtual void UseWeapon();

	UFUNCTION(BlueprintImplementableEvent)
	void Spawn();
};

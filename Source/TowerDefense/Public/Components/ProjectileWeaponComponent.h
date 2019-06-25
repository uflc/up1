// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponComponent.h"
#include "ProjectileWeaponComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API UProjectileWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector ProjectileRelativeSpawnPoint;

	virtual void UseWeapon() override;
};

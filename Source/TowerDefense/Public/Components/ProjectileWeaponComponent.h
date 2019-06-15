// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UProjectileWeaponComponent();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector ProjectileRelativeSpawnPoint;

public:
	virtual void UseWeapon() override;
};

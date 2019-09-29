// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponComponent.h"
#include "DirectWeaponComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API UDirectWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()
	
public:
	UDirectWeaponComponent();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector EffectRelativeSpawnPoint;

	UPROPERTY()
	class UEffectorComponent* Effector;

public:
	virtual void SetCommonData(UTDWeaponCommonData* InData) override;

	virtual void UseWeapon() override;
};

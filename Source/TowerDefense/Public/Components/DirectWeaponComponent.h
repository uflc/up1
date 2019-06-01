// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "DirectWeaponComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UDirectWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()
	
public:
	UDirectWeaponComponent();

protected:
	UPROPERTY()
	class UEffectorComponent* Effector;

public:
	virtual void SetCommonData(UTDWeaponCommonData* InData) override;

	virtual void UseWeapon() override;
};

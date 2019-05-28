// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "UnitSkillComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UUnitSkillComponent : public UWeaponComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUnitSkillComponent();

protected:

public:
	// Change to virtual?
	UFUNCTION(BlueprintCallable)
	virtual void InitializeSkillComp(const float InCooldown);

	// Need?
	UFUNCTION(BlueprintCallable)
	virtual void CastSkill(class UObject* InTarget) {}
};

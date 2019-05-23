// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "DirectWeaponComponent.generated.h"

/**
 * 
 */
class ATDCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UDirectWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()

	UDirectWeaponComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbook* EffectFlipbook;

public:
	// Change to virtual?
	UFUNCTION(BlueprintCallable)
	void InitializeDirectAttackComp();

	virtual void UseWeapon() override;

	//Old func
	virtual void ExecAttack(ATDCharacter* Target) override;
};

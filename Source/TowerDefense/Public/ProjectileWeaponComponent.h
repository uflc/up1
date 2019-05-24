// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "ProjectileWeaponComponent.generated.h"

/**
 * 
 */
class ATDCharacter;
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UProjectileWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()
public:
	UProjectileWeaponComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ProjectileRelativeSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AHomingProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ProjectileisDirectable;

public:
	// Change to virtual?
	UFUNCTION(BlueprintCallable)
	void InitializeProjectileAttackComp();

	virtual void UseWeapon() override;

	//Deprecated
	virtual void ExecAttack(ATDCharacter* Target) override;
};

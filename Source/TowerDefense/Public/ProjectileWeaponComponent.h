// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "ProjectileWeaponComponent.generated.h"

/**
 * 
 */
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
	TSubclassOf<class ABulletBase> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ProjectileisDirectable;

public:
<<<<<<< HEAD
	virtual void ExecAttack(class UObject* Target) override;

	UFUNCTION(BlueprintCallable)
	void Initialize(const FVector inVector,TSubclassOf<ABulletBase> inClass,bool inDirectable){
	ProjectileRelativeSpawnPoint=inVector; 
	ProjectileClass=inClass;
	ProjectileisDirectable= inDirectable;
	}
=======
	virtual void ExecAttack(class ATDCharacter* Target) override;

	virtual void Work() override;

<<<<<<< HEAD:Source/TowerDefense/Public/ProjectileWeaponComponent.h
	UFUNCTION(BlueprintCallable)
	void InitializeRangedComp(const float inRange, const FVector inVector, UClass* inClass, bool inDirectable);
=======
	void Initialize() override;

	void Initialize(const FVector inVector, UClass* inClass, bool inDirectable);

	void Initialize(const float inRange, const FVector inVector, UClass* inClass, bool inDirectable);
>>>>>>> 9dbd6eed48176c0144435ed0a4729a740d1f2351
>>>>>>> origin/master:Source/TowerDefense/Public/RangedAttackComponent.h
};

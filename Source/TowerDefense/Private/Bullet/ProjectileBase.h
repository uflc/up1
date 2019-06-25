// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "TDTypes.h"
#include "ProjectileBase.generated.h"

UCLASS(Abstract)
class TOWERDEFENSE_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileBase();

protected:
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
	class UTDProjectileCommonData* ProjectileCommon;

	UPROPERTY(Category = Attack, VisibleAnywhere, BlueprintReadOnly)
	class ATDCharacter* Target;

	UPROPERTY(Category = Animation, VisibleAnywhere, BlueprintReadOnly)
	class UPaperFlipbookComponent* Animation;

	UPROPERTY(Category = Attack, VisibleAnywhere)
	class UEffectorComponent* Effector;

public:
	void SetTarget(ATDCharacter* InTarget) { Target = InTarget; }

	virtual void SetCommonData(UTDProjectileCommonData* InData, FEffectorData EffectorData, bool bShouldTick = false);
	
	virtual void BulletDestroy();

	FORCEINLINE UEffectorComponent* GetEffector() const { return Effector; }
};

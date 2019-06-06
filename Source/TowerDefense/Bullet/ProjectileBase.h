// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
	float Velocity;

	UPROPERTY(Category = Attack, VisibleAnywhere, BlueprintReadOnly)
	class ATDCharacter* Target;

	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
	class UPaperFlipbookComponent* Animation;

	UPROPERTY(Category = Attack, VisibleAnywhere)
	class UEffectorComponent* Effector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsDirectable;
public:	
	void SetTarget(ATDCharacter* InTarget) { Target = InTarget; }

	virtual void SetCommonData(UTDProjectileCommonData* InData);

	virtual void SetEffector(float EffectRange, uint32 Damage);

	virtual void SetEffector(const TArray<FDebuff>& InDebuffArray);
	
	virtual void BulletDestroy();
};

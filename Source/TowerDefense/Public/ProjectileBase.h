// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS(Abstract)
class TOWERDEFENSE_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
	class UTDProjectileCommonData* ProjectileCommon;

	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadWrite)
	float Velocity;

	UPROPERTY(Category = Unit, VisibleAnywhere, BlueprintReadWrite)
	class ATDCharacter* Target;

	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
	class UPaperFlipbookComponent* Animation;

	UPROPERTY()
	class UEffectorComponent* Effector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDirectable;
public:	
	void SetTarget(ATDCharacter* InTarget) { Target = InTarget; }

	virtual void SetCommonData(UTDProjectileCommonData* InData);

	virtual void SetEffector(float EffectRange, uint32 Damage);

	virtual void BulletDestroy();
};

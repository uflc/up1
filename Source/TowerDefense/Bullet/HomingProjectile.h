// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "HomingProjectile.generated.h"

UCLASS()
class TOWERDEFENSE_API AHomingProjectile : public AProjectileBase
{
	GENERATED_BODY()
	
public:	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector VelocityVec;

	float SplashRange;

	FVector GetDistanceVecToTarget();

	virtual void CalcVelocityVec(const FVector& DirectionVec);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

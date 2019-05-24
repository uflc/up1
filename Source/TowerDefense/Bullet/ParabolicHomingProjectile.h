// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HomingProjectile.h"
#include "ParabolicHomingProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AParabolicHomingProjectile : public AHomingProjectile
{
	GENERATED_BODY()
	
protected:
	////UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FVector VelocityVec;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurveScale;

	float TickCounter;

	FVector DefVelocityVec;

	float DefVecSize;

	virtual void CalcVelocityVec(const FVector& DirectionVec) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Initialize(ATDCharacter* iTarget, int32 iDamage, bool iIsDirectable, float iSplashRange);
};

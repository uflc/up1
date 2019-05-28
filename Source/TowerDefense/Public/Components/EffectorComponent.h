// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDComponent.h"
#include "EffectorComponent.generated.h"

/**
 * 
 */
 class ATDCharacter;

UCLASS(Blueprintable, Abstract, ClassGroup = (Custom))
class TOWERDEFENSE_API UEffectorComponent : public UTDComponent
{
	GENERATED_BODY()

protected:
	//Need it for cache?

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EffectRange;

	//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TMap<> AffectRateByDistanceMap;

public:
	virtual void Effect(ATDCharacter* Target) {}

	void InitializeEffectorComponent(float InEffectRange);

	UFUNCTION(BlueprintCallable)
	void AffectTarget(ATDCharacter* MainTarget);
};

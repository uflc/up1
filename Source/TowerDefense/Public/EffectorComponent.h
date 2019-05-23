// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDComponent.h"
#include "EffectorComponent.generated.h"

/**
 * 
 */
 class ATDCharacter;

UCLASS(Blueprintable, Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UEffectorComponent : public UTDComponent
{
	GENERATED_BODY()
public:
	UEffectorComponent();
protected:
	//Need it for cache?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AffectRange;

public:
	virtual void Affect(ATDCharacter* Target){}

	//void SplashAffect();

	void SplashAffect(const ATDCharacter* MainTarget);
};

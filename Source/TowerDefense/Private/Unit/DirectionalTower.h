// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/Tower.h"
#include "UObject/ObjectMacros.h"
#include "DirectionalTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ADirectionalTower : public ATower
{
	GENERATED_BODY()
	
public:
	ADirectionalTower(const FObjectInitializer& ObjectInitializer);

	void SetFlipbooks() override;
};

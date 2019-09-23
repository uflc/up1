// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "Data/PassiveCommonData.h"
#include "BaseAuraComponent.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UBaseAuraComponent : public UPassiveCommonData
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	class UBoxComponent* BoxCollision;

public:
	virtual void Initialize_Implementation();
};

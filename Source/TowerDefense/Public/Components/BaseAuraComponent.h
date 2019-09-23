// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "PassiveSkillComponent.h"
#include "BaseAuraComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class TOWERDEFENSE_API UBaseAuraComponent : public UPassiveSkillComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCollision;

public:
	UBaseAuraComponent();

	virtual void Initialize_Implementation();
};

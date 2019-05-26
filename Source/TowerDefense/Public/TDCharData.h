// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDUnitCommonData.h"
#include "TDCharData.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDCharData : public UTDUnitCommonData
{
	GENERATED_BODY()
	
	friend class ATDCharacter;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDChar|Property")
	float DefaultAggroDrawnRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDChar|Property")
	float DefaultDrawingAggroRange;
};

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
		
protected:
	UPROPERTY(EditAnywhere, Category = "TDChar|Property")
	float DefaultAggroDrawnRange;

	UPROPERTY(EditAnywhere, Category = "TDChar|Property")
	float DefaultDrawingAggroRange;

public:
	FORCEINLINE const float& GetAggroDrawnRange() const { return DefaultAggroDrawnRange; }
	FORCEINLINE const float& GetDrawingAggroRange() const { return DefaultDrawingAggroRange; }

};

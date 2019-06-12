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
	//if 0.0f TDCharacter will use AttackRange as AggroRange.
	UPROPERTY(EditAnywhere, Category = "TDChar")
	float DefaultAggroDrawnRange;

	//deprecated.
	UPROPERTY(EditAnywhere, Category = "TDChar")
	float DefaultDrawingAggroRange;

	//Need? CDO also can set default Health...
	UPROPERTY(EditAnywhere, Category = "TDChar")
	int32 DefaultHealth;

public:
	FORCEINLINE const float& GetAggroDrawnRange() const { return DefaultAggroDrawnRange; }
	FORCEINLINE const float& GetDrawingAggroRange() const { return DefaultDrawingAggroRange; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetHealth() const { return DefaultHealth; }
};

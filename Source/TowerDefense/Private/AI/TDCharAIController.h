// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDAIController.h"
#include "TDCharAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDCharAIController : public ATDAIController
{
	GENERATED_BODY()

public:
	static const FName DestinationKey;

	UFUNCTION(BlueprintCallable)
	void SetDestination(const FVector Destination);

	float GetDestination();


};

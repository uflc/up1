// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TDAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDAIController : public AAIController
{
	GENERATED_BODY()

public:
	static const FName DestinationKey;
	static const FName AggroTargetKey;

	//todo runbehavior tree use blackboard
	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetDestination(const FVector Destination);
};

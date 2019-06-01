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
	
private:
	//class UBlackboardComponent* Blackboard;

protected:
	//todo runbehavior tree use blackboard
	//void BeginPlay() override;

public:
	virtual void SetDestination(const FVector Destination);
};

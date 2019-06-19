// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/TDCharAIController.h"
#include "EnemyTDCharAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AEnemyTDCharAIController : public ATDCharAIController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<uint8> DestBranchIdxQ;

	//UFUNCTION()
	//void InitDestinationQueue(const TArray<uint8>& InDestinationQueue);
};

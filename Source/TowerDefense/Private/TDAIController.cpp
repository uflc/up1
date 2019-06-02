// Fill out your copyright notice in the Description page of Project Settings.


#include "TDAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TDCharacter.h"
#include "Tower.h"
#include "TowerDefense.h"

const FName ATDAIController::DestinationKey(TEXT("Destination"));
const FName ATDAIController::AggroTargetKey(TEXT("AggroTarget"));

void ATDAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//todo findobject BBAsset, BTAsset then use / run.

	UClass* PawnClass = InPawn->GetClass();
	TD_LOG(Warning, TEXT("PawnClass: %s"), *PawnClass->GetName());

	if (PawnClass == ATDUnit::StaticClass())
	{
		TD_LOG(Warning, TEXT("ATDUnit"));
	}

	if (PawnClass == ATDCharacter::StaticClass())
	{
		TD_LOG(Warning, TEXT("ATDCharacter"));
	}

	if (PawnClass == ATower::StaticClass())
	{
		TD_LOG(Warning, TEXT("ATower"));
	}
	
}

void ATDAIController::SetDestination(const FVector Destination)
{
	if (!Blackboard) return;

	Blackboard->SetValueAsVector(DestinationKey, Destination);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCharAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ATDCharAIController::DestinationKey(TEXT("Destination"));

void ATDCharAIController::SetDestination(const FVector Destination)
{
	if (!Blackboard) return;

	Blackboard->SetValueAsVector(DestinationKey, Destination);
}

float ATDCharAIController::GetDestination()
{
	return Blackboard ? Blackboard->GetValueAsFloat(DestinationKey) : 0.0f;
}

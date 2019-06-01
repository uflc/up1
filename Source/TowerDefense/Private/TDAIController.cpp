// Fill out your copyright notice in the Description page of Project Settings.


#include "TDAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void ATDAIController::SetDestination(const FVector Destination)
{
	static FName DestinationKey = TEXT("Destination");
	if (!Blackboard) return;

	Blackboard->SetValueAsVector(DestinationKey, Destination);
}

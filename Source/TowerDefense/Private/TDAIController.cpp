// Fill out your copyright notice in the Description page of Project Settings.


#include "TDAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "TDCharacter.h"
#include "TDUnit.h"
#include "Tower.h"
#include "TowerDefense.h"

const FName ATDAIController::DestinationKey(TEXT("Destination"));
const FName ATDAIController::AggroTargetKey(TEXT("AggroTarget"));
const FName ATDAIController::AttackRangeKey(TEXT("AttackRange"));

void ATDAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UClass* PawnClass = InPawn->GetClass();
	TD_LOG(Warning, TEXT("PawnClass: %s"), *PawnClass->GetName());

	TDUnit = Cast<ATDUnit>(InPawn);
	if (!TDUnit) return;
	
	TDUnit->OnWeaponChanged.AddDynamic(this, &ATDAIController::ReceiveWeaponChange);
	ReceiveWeaponChange();

	if (BBAsset && BTAsset)
	{
		UseBlackboard(BBAsset, Blackboard);
		RunBehaviorTree(BTAsset);
	}
}

void ATDAIController::SetDestination(const FVector Destination)
{
	if (!Blackboard) return;

	Blackboard->SetValueAsVector(DestinationKey, Destination);
}

void ATDAIController::SetAttackRange(const float AttackRange)
{
	if (!Blackboard) return;

	Blackboard->SetValueAsFloat(AttackRangeKey, AttackRange);
}

void ATDAIController::ReceiveWeaponChange()
{
	if (!TDUnit) return;

	SetAttackRange(TDUnit->GetAttackRange());
}

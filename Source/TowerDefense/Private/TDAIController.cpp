// Fill out your copyright notice in the Description page of Project Settings.


#include "TDAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
//#include "Navigation/CrowdFollowingComponent.h"
#include "TDCharacter.h"
#include "Tower.h"
#include "TowerDefense.h"

const FName ATDAIController::DestinationKey(TEXT("Destination"));
const FName ATDAIController::AggroTargetKey(TEXT("AggroTarget"));
const FName ATDAIController::AttackRangeKey(TEXT("AttackRange"));

ATDAIController::ATDAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer/*.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent"))*/) {}

void ATDAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

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

AActor* ATDAIController::GetAggroTarget()
{
	return 	Blackboard ? Cast<AActor>(Blackboard->GetValueAsObject(AggroTargetKey)) : nullptr;
}

float ATDAIController::GetDestination()
{
	return Blackboard ? Blackboard->GetValueAsFloat(DestinationKey) : 0.0f;
}

void ATDAIController::ReceiveWeaponChange()
{
	if (!TDUnit) return;

	SetAttackRange(TDUnit->GetAttackRange());
}

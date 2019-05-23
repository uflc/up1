// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "TowerDataTree.h"
#include "TDPlayerController.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
//#include "PaperSpriteComponent.h"
//#include "TDCharacter.h"
//#include "TDUnitCommonData.h"
#include "TowerDefense.h" //log 


void ATower::BeginPlay()
{
	Super::BeginPlay();
	TotalCost = TowerData->Cost;
}

void ATower::OnDeselected()
{
	IsSelected = false;
}

void ATower::ShowActionMenu()
{
	GetWorld()->GetFirstPlayerController<ATDPlayerController>()->ShowTowerActionMenu(this);
}

UPaperFlipbook * ATower::GetDesiredAnimation()
{
	return TowerData->GetMatchingAnim(Direction, UnitState);
}

bool ATower::UpdateAnimation()
{
	if (!Super::UpdateAnimation()) return false;

	return true;
}

void ATower::UpdateDirection()
{
	EDirection OldDirection = Direction;

	//@TODO Aggro Target AActor
	FVector DirectionVec= ((AActor*) AggroTarget)->GetActorLocation() - GetActorLocation();

	Direction = DirectionVec.X > 0 ?
				(DirectionVec.Y > 0 ? EDirection::RT : EDirection::RD)
			  : (DirectionVec.Y > 0 ? EDirection::LT : EDirection::LD);

	if (!(OldDirection == Direction))
		UpdateAnimation();
}

bool ATower::Upgrade_Implementation(ETowerType UpType)
{
	UTowerData* Upgraded = TowerData->GetNextUpgraded(UpType);

	if (!Upgraded) return false;

	TowerData = Upgraded;

	AttackDamage = Upgraded->AttackDamage;
	AttackRange = Upgraded->AttackRange;
	AttackDelay = Upgraded->AttackSpeed;
	TotalCost += Upgraded->Cost;

	UpdateAnimation();

	return true;
}

void ATower::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	TD_LOG_CALLONLY(Warning);////

	if (IsSelected) return;

	IsSelected = true;
	ShowActionMenu();
}
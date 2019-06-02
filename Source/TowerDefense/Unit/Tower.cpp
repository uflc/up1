// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "TowerDataTree.h"
#include "TDPlayerController.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "TowerDefense.h" //log 


ATower::ATower()
{
	static FName TowerCollisionProfileName(TEXT("BlockAll"));
	Animation->SetCollisionProfileName(TowerCollisionProfileName);

	Team = EUnitTeam::Player;
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	const UTowerData* TowerData = Cast<UTowerData>(UnitData);

	if (TowerData)
	{
		TotalCost = TowerData->Cost;
	}
}

void ATower::OnDeselected()
{
	bIsSelected = false;
}

void ATower::ShowActionMenu()
{
	GetWorld()->GetFirstPlayerController<ATDPlayerController>()->ShowTowerActionMenu(this);
}

UPaperFlipbook * ATower::GetDesiredAnimation()
{
	//Animation of current level, direction and state, �ø��� �迭 ������ �Ʒ� �İ� ��Ī �Ǿ� ��.
	return UnitData ? UnitData->GetAnimations()[((uint8) Direction * 2) + (uint8)UnitState].Get() : nullptr;
}

bool ATower::UpdateAnimation()
{
	UpdateDirection();
	if (!Super::UpdateAnimation()) return false;

	return true;
}

void ATower::UpdateDirection()
{
	//@TODO Aggro Target AActor
	if (!AggroTarget) return;

	FVector DirectionVec= ((AActor*) AggroTarget)->GetActorLocation() - GetActorLocation();

	//ž���� XY ��鿡�� X�� �������� ���, Y�� �Ʒ����� ���.
	Direction = DirectionVec.X > 0 ?
				(DirectionVec.Y < 0 ? EDirection::RT : EDirection::RD)
			  : (DirectionVec.Y < 0 ? EDirection::LT : EDirection::LD);
}

bool ATower::Upgrade_Implementation(ETowerType UpType)
{
	UTowerData* TowerData = Cast<UTowerData>(UnitData);
	if (!TowerData) return false;

	UTowerData* Upgraded = TowerData->GetNextUpgraded(UpType);
	if (!Upgraded) return false;

	UnitData = Upgraded;
	TotalCost += Upgraded->Cost;

	UpdateAnimation();

	return true;
}

void ATower::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	TD_LOG_CALLONLY(Warning);////

	if (bIsSelected) return;

	bIsSelected = true;
	ShowActionMenu();
}
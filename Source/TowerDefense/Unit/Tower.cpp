// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "TowerDataTree.h"
#include "TDPlayerController.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "TowerDefense.h" //log 


ATower::ATower()
{
	static FName TowerCollisionProfileName(TEXT("NoCollision"));
	Animation->SetCollisionProfileName(TowerCollisionProfileName);
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	const UTowerData* TowerData = Cast<UTowerData>(Common);
	if (TowerData)
	{
		TotalCost = TowerData->Cost;
	}
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
	return Common ? Common->Animations[((uint8)Direction) + ((uint8)UnitState * 4/*EDirection::NumEnums*/)].Get() : nullptr;
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
	UTowerData* TowerData = Cast<UTowerData>(Common);
	if (!TowerData) return false;

	UTowerData* Upgraded = TowerData->GetNextUpgraded(UpType);

	if (!Upgraded) return false;

	Common = Upgraded;

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
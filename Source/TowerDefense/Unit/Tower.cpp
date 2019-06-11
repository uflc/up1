// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "TowerDataTree.h"
#include "TDPlayerController.h" ////showtoweractionmenu
#include "TDAIController.h" //
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "WeaponComponent.h" //upgrade
#include "Components/BoxComponent.h"
#include "TowerDefense.h" //log 


ATower::ATower()
{
	static FName TowerCollisionProfileName(TEXT("BlockAll"));
	static const FVector BoxExtent(125.0f, 75.0f, 50.0f);
	Box->InitBoxExtent(BoxExtent);
	Box->SetCollisionProfileName(TowerCollisionProfileName);
	Box->SetCanEverAffectNavigation(false);

	static FName VisibiltyProfileName(TEXT("UI"));
	Animation->SetCollisionProfileName(VisibiltyProfileName);
	Animation->SetRelativeLocation(FVector(0.0f, -150.0f, 0.0f));
	Animation->SetupAttachment(Box);

	Team = EUnitTeam::Player;
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	const UTowerData* TowerData = Cast<UTowerData>(UnitData);

	if (TowerData)
	{
		TotalCost = TowerData->GetCost();
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

void ATower::FaceTo(AActor* Target)
{
	if (!Target) return;

	const EDirection OldDirection = Direction;
	const FVector DirToTarget = Target->GetActorLocation() - GetActorLocation();
	Direction = DirToTarget.X > 0 ? DirToTarget.Y > 0 ? EDirection::RD : EDirection::RT
								  : DirToTarget.Y > 0 ? EDirection::LD : EDirection::LT;
	if (OldDirection != Direction)
	{
		UpdateAnimation();
	}
}

void ATower::FaceToAggroTarget()
{
	if (!Controller) return;
	
	FaceTo(Cast<ATDAIController>(Controller)->GetAggroTarget());
}

float ATower::GetTowerRange_Implementation()
{
	return GetAttackRange();
}

bool ATower::Upgrade_Implementation(ETowerType UpType)
{
	UTowerData* TowerData = Cast<UTowerData>(UnitData);
	if (!TowerData) return false;

	UTowerData* Upgraded = TowerData->GetNextUpgraded(UpType);
	if (!Upgraded) return false;

	UnitData = Upgraded;
	TotalCost += Upgraded->GetCost();

	CreateUniqueWeapon();

	UpdateAnimation();

	return true;
}

void ATower::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	TD_LOG_CALLONLY(Warning);//

	if (bIsSelected) return;

	bIsSelected = true;
	ShowActionMenu();
}

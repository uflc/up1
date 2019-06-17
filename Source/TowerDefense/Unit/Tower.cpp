// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "TowerDataTree.h"
#include "TDPlayerController.h"
#include "TDAIController.h"
#include "PaperFlipbook.h"
#include "Components/TDPaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "WeaponComponent.h"
#include "Components/BoxComponent.h"
#include "NavArea_Null.h"
#include "TowerDefense.h"


ATower::ATower()
{
	InitializeDefaults();
}

ATower::ATower(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	InitializeDefaults();
}

void ATower::InitializeDefaults()
{
	static const FVector BoxExtent(137.5f, 100.0f, 5.0f);
	Box->InitBoxExtent(BoxExtent);
	Box->bDynamicObstacle = true;
	Box->AreaClass = UNavArea_Null::StaticClass();

	static FName VisibiltyProfileName(TEXT("UI"));
	Animation->SetCollisionProfileName(VisibiltyProfileName);
	Animation->SetRelativeLocation(FVector(0.0f, -100.0f, 0.0f));

	if (Shadow)
	{
		Shadow->SetRelativeLocation(FVector(0.0f, -0.1f, -240.0f));
	}

	Team = EUnitTeam::Player;
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
}

void ATower::PostInitializeComponents()
{
	Super::PostInitializeComponents();

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

	ApplyData();

	return true;
}

void ATower::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	TD_LOG_C(Warning);//

	if (bIsSelected) return;

	bIsSelected = true;
	ShowActionMenu();
}

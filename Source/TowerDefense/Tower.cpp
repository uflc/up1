// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "MyUMGGameModeBase.h"
#include "Engine/Engine.h"
#include "HUDWidget.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;
} 

void ATower::OnDeselected()
{
	IsSelected = false;
}

void ATower::ShowActionMenu()
{
	if (IsSelected) return;

	UHUDWidget* HUD = Cast<UHUDWidget>(GetWorld()->GetAuthGameMode<AMyUMGGameModeBase>()->GetCurrentWidget());

	if (HUD)	HUD->ShowTowerActionMenu(this);
}

inline FString ATower::GetPresetName()
{
	return "";
}

FString ATower::GetTowerStatusText()
{
	return "Tower Status Test";
}

FString ATower::GetTowerDescriptionText()
{
	return "Tower Description Test";
}

inline float ATower::GetTowerRange() { return 0.0f; }

inline float ATower::GetTowerAttackSpd(){	return 0.0f; }

inline int32 ATower::GetTowerAttackDmg() { return 0; }

void ATower::UpdateAnimationCPP()
{
	auto Flipbook= Cast<UPaperFlipbookComponent>(GetComponentByClass(UPaperFlipbookComponent::StaticClass()));

	Flipbook->SetFlipbook(GetFlipbookOfCurrentState().Get());

	switch (TowerState) {
		case ETowerState::TS_Idle:
		default:
		Flipbook->PlayFromStart();
		Flipbook->SetLooping(true);
		break;

		case ETowerState::TS_Action:
		Flipbook->PlayFromStart();
		Flipbook->SetLooping(false);
		break;
	}
}

TSoftObjectPtr<UPaperFlipbook> ATower::GetFlipbookOfCurrentState()
{
	return NULL;
}

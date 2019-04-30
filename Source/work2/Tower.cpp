// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "MyUMGGameModeBase.h" //test
#include "Engine/Engine.h"
#include "HUDWidget.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;
} 

//const float ATower::AttackDamage = 0.0f;
//const float ATower::AttackSpeed = 0.0f;
//const float ATower::AttackRange = 0.0f;

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

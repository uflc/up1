// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "TowerUpDataTree.h"
#include "TDGameModeBase.h"
#include "HUDWidget.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
//#include "PaperSpriteComponent.h"
//#include "TDCharacter.h"
//#include "TDUnitCommonData.h"
#include "TowerDefense.h" //log 


void ATower::OnDeselected()
{
	IsSelected = false;
}

//void ATower::OnSelected(UPrimitiveComponent * TouchedComponent, FKey ButtonPressed)
//{
//	if (IsSelected) return;
//
//	IsSelected = true;
//	ShowActionMenu();
//}

void ATower::ShowActionMenu()
{
	UHUDWidget* HUD = Cast<UHUDWidget>(GetWorld()->GetAuthGameMode<ATDGameModeBase>()->GetCurrentWidget());

	if (HUD)	HUD->ShowTowerActionMenu(this);
}

UPaperFlipbook * ATower::GetDesiredAnimation()
{
	return UpgradeTree->GetMatchingAnim(Direction, UnitState);
}

bool ATower::UpdateAnimation()
{
	if (!Super::UpdateAnimation()) return false;

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
//
//inline FString ATower::GetPresetName()
//{
//	return "";
//}
//
//FString ATower::GetTowerStatusText()
//{
//	return "Tower Status Test";
//}
//
//FString ATower::GetTowerDescriptionText()
//{
//	return "Tower Description Test";
//}
//
//inline float ATower::GetTowerRange() { return 0.0f; }
//
//inline float ATower::GetTowerAttackSpd(){	return 0.0f; }
//
//inline int32 ATower::GetTowerAttackDmg() { return 0; }

//void ATower::UpdateAnimationCPP()
//{
//	UPaperFlipbookComponent* Sprite = GetSprite();
//	if (!Sprite) return;
//
//	Sprite->SetFlipbook(GetFlipbookOfCurrentState().Get());
//
//	/*switch (TowerState) {
//		case ETowerState::TS_Idle:
//		default:
//			Sprite->PlayFromStart();
//			Sprite->SetLooping(true);
//		break;
//
//		case ETowerState::TS_Action:
//			Sprite->PlayFromStart();
//			Sprite->SetLooping(false);
//		break;
//	}*/
//}
//
//TSoftObjectPtr<UPaperFlipbook> ATower::GetFlipbookOfCurrentState()
//{
//	return nullptr;
//}

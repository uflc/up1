// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "TDGameModeBase.h"
//#include "Engine/Engine.h"
#include "HUDWidget.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"


ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateOptionalDefaultSubobject<USceneComponent>("DummyRoot");
	RootScene->SetupAttachment(GetRootComponent());
	Shadow = CreateOptionalDefaultSubobject<UPaperSpriteComponent>("Shadow");
	Shadow->SetupAttachment(RootScene);
	Shadow->SetRelativeLocationAndRotation(FVector(0,250.0f,-0.1f),FRotator(0,0,-90));
	Sprite = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>("Sprite");
	Sprite->SetupAttachment(RootScene);
	Sprite->SetRelativeRotation(FRotator(0,0,-90));
//	Sprite->OnClicked.AddDynamic(this,&ATower::OnSpriteSelected);
} 

void ATower::OnDeselected()
{
	IsSelected = false;
}

void ATower::OnSpriteSelected(UPrimitiveComponent * TouchedComponent, FKey ButtonPressed)
{
	ShowActionMenu();
}

void ATower::ShowActionMenu()
{
	if (IsSelected) return;

	UHUDWidget* HUD = Cast<UHUDWidget>(GetWorld()->GetAuthGameMode<ATDGameModeBase>()->GetCurrentWidget());

	if (HUD)	HUD->ShowTowerActionMenu(this);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("ShowActionMenu"));
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
	Sprite->SetFlipbook(GetFlipbookOfCurrentState().Get());

	switch (TowerState) {
		case ETowerState::TS_Idle:
		default:
			Sprite->PlayFromStart();
			Sprite->SetLooping(true);
		break;

		case ETowerState::TS_Action:
			Sprite->PlayFromStart();
			Sprite->SetLooping(false);
		break;
	}
}

TSoftObjectPtr<UPaperFlipbook> ATower::GetFlipbookOfCurrentState()
{
	return NULL;
}

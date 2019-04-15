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
	TowerTypeNum=0;
	TowerState=ETowerState::TS_Idle;
} 

//const float ATower::AttackDamage = 0.0f;
//const float ATower::AttackSpeed = 0.0f;
//const float ATower::AttackRange = 0.0f;

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATower::ShowActionMenu()
{
	//if (bIsActionMenuDisplayed) return;

	////to use GEngine include engine/engine.h not public engine.h for iwyu
	//UHUDWidget* HUDWidget = Cast<UHUDWidget>(GEngine->GetWorld()->GetAuthGameMode<AMyUMGGameModeBase>()->GetCurrentWidget());
	//HUDWidget->ShowTowerActionMenu(this);

	//bIsActionMenuDisplayed = true;
}

void ATower::HideActionMenu()
{
	//if (!bIsActionMenuDisplayed) return;

	//UHUDWidget* HUDWidget = Cast<UHUDWidget>(GEngine->GetWorld()->GetAuthGameMode<AMyUMGGameModeBase>()->GetCurrentWidget());
	//HUDWidget->HideTowerActionMenu();

	//bIsActionMenuDisplayed = false;
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

inline float ATower::GetTowerAttackDmg() { return 0.0f; }

void ATower::UpdateAnimationCPP()
{
	Cast<UPaperFlipbookComponent>(GetComponentByClass(UPaperFlipbookComponent::StaticClass()))->SetFlipbook(GetFlipbookOfCurrentState().Get());
}

//void ATower::ResponseButtonEvent(int iNum)
//{
//	switch (iNum)
//	{
//	case 0:
//	return;
//		default:
//		return;
//	}
//}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


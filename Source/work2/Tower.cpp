// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "MyUMGGameModeBase.h" //test
#include "Engine/Engine.h"
#include "HUDWidget.h"


// Sets default values
ATower::ATower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//use if c++ only
	//OnClicked.AddDynamic(this, &ATower::Selected);
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


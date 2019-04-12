// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerWizard.h"
#include "Engine.h"

ATowerWizard::ATowerWizard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnClicked.AddDynamic(this, &ATowerWizard::Selected);
}


float ATowerWizard::TowerAttackRange = 700.0f;
float ATowerWizard::TowerAttackSpeed = 2.0f;
float ATowerWizard::TowerAttackDmg = 200.0f;

// Called when the game starts or when spawned
void ATowerWizard::BeginPlay()
{
	Super::BeginPlay();

}

void ATowerWizard::Selected(AActor * TouchedActor, FKey ButtonPressed)
{
	ShowActionMenu();
	// PlaySoundEffect();
}

void ATowerWizard::ShowActionMenu()
{
	//if (bIsActionMenuDisplayed) return;

	//ActionMenu is not displayed now

	//auto widget = Cast<AMyUMGGameModeBase>(GEngine->GetWorld()->GetAuthGameMode())->GetCurrentWidget()

	// TODO :: Complete this
	//auto towerwidget = Cast<UWidgetTowerBase>(Cast<AMyUMGGameModeBase>(GEngine->GetWorld()->GetAuthGameMode())->GetTowerWidget());
	//towerwidget->SelectPreset("Empty");
}

void ATowerWizard::HideActionMenu()
{
}

inline FString ATowerWizard::GetPresetName()
{
	return "Wizard";
}

FString ATowerWizard::GetTowerStatusText()
{
	return "TowerWizard Status Test";
}

FString ATowerWizard::GetTowerDescriptionText()
{
	return "TowerWizard Description Test";
}

inline float ATowerWizard::GetTowerRange() { return ATowerWizard::TowerAttackRange + 0.0f; }
inline float ATowerWizard::GetTowerAttackSpd() { return ATowerWizard::TowerAttackSpeed + 0.0f; }
inline float ATowerWizard::GetTowerAttackDmg() { return ATowerWizard::TowerAttackDmg + 0.0f; }

//void ATowerWizard::ResponseButtonEvent(int iNum)
//{
//	switch (iNum)
//	{
//	case 0:
//		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "Button 0 : Upgrade");
//		//GEngine->GetWorld()->GetAuthGameMode<AMyUMGGameModeBase>()->ChangeTower(this,ATowerArcher);
//		return;
//	case 1:
//		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "Button 1 : Sell");
//		//GEngine->GetWorld()->GetAuthGameMode<AMyUMGGameModeBase>()->ChangeTower(this, ATowerEmpty);
//		return;
//	case 2:
//		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "Button 2 : Close");
//		return;
//	default:
//		return;
//	}
//}

// Called every frame
void ATowerWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
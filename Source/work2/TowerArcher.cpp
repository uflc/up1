// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerArcher.h"
#include "TowerEmpty.h"
#include "UITowerBase.h"
#include "MyUMGGameModeBase.h"
#include "Engine.h"

ATowerArcher::ATowerArcher()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnClicked.AddDynamic(this, &ATowerArcher::Selected);
}

// Called when the game starts or when spawned
void ATowerArcher::BeginPlay()
{
	Super::BeginPlay();

}

void ATowerArcher::Selected(AActor * TouchedActor, FKey ButtonPressed)
{
	ShowActionMenu();
	// PlaySoundEffect();
}

void ATowerArcher::ShowActionMenu()
{
}

void ATowerArcher::HideActionMenu()
{
}

inline FString ATowerArcher::GetPresetName()
{
	return "Archer";
}

//void ATowerArcher::ResponseButtonEvent(int iNum)
//{
//	switch (iNum)
//	{
//	case 0:
//		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "Button 0 : Upgrade");
//		//GEngine->GetWorld()->GetAuthGameMode<AMyUMGGameModeBase>()->ChangeTower(this,ATowerArcher);
//		return;
//	case 1:
//		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "Button 1 : Sell");
//		//GEngine->GetWorld()->GetAuthGameMode<AMyUMGGameModeBase>()->ChangeTower(this,ATowerEmpty);
//		return;
//	case 2:
//		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "Button 2 : Close");
//		return;
//	default:
//		return;
//	}
//}

// Called every frame
void ATowerArcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FString ATowerArcher::GetTowerStatusText()
{
	return "TowerArcher Status Test";
}

FString ATowerArcher::GetTowerDescriptionText()
{
	return "TowerArcher Description Test";
}

inline float ATowerArcher::GetTowerRange() { return 0.0f; }

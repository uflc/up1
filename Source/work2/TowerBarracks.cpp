// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerBarracks.h"
#include "TowerEmpty.h"
#include "UITowerBase.h"
#include "MyUMGGameModeBase.h"
#include "Engine.h"

ATowerBarracks::ATowerBarracks()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnClicked.AddDynamic(this, &ATowerBarracks::Selected);
}

// Called when the game starts or when spawned
void ATowerBarracks::BeginPlay()
{
	Super::BeginPlay();

}

void ATowerBarracks::Selected(AActor * TouchedActor, FKey ButtonPressed)
{
	ShowActionMenu();
	// PlaySoundEffect();
}

void ATowerBarracks::ShowActionMenu()
{
}

void ATowerBarracks::HideActionMenu()
{
}

inline FString ATowerBarracks::GetPresetName()
{
	return "Barracks";
}

FString ATowerBarracks::GetTowerStatusText()
{
	return "TowerBarracks Status Test";
}

FString ATowerBarracks::GetTowerDescriptionText()
{
	return "TowerBarracks Description Test";
}

inline float ATowerBarracks::GetTowerRange() { return 0.0f; }

//void ATowerBarracks::ResponseButtonEvent(int iNum)
//{
//	switch (iNum)
//	{
//	case 0:
//		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "Button 0 : Upgrade");
//		//GEngine->GetWorld()->GetAuthGameMode<AMyUMGGameModeBase>()->ChangeTower(this,ATowerBarracks);
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
void ATowerBarracks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

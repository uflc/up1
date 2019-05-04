// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerBarracks.h"
#include "TowerEmpty.h"
#include "UITowerBase.h"
#include "MyUMGGameModeBase.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Engine.h"

ATowerBarracks::ATowerBarracks()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

inline float ATowerBarracks::GetTowerRange() { return 700.0f; }

TSoftObjectPtr<UPaperFlipbook> ATowerBarracks::GetFlipbookOfCurrentState()
{
	return ATowerBarracks::FlipbookMap.Find(TowerState)->GetData()[TowerTypeNum - 1].Get();
}

TMap<ETowerState, TArray<TSoftObjectPtr<UPaperFlipbook>>> ATowerBarracks::FlipbookMap =
{
	{
		ETowerState::TS_Idle ,TArray<TSoftObjectPtr<UPaperFlipbook>>
		{
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Barracks/Building/1/Barracks1Idle.Barracks1Idle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Barracks/Building/2/Barracks2Idle.Barracks2Idle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Barracks/Building/3/Barracks3Idle.Barracks3Idle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Barracks/Building/4/Barracks4Idle.Barracks4Idle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Barracks/Building/5/Barracks5Idle.Barracks5Idle'"), NULL, LOAD_None, NULL)}
		},
	{
		ETowerState::TS_Action,TArray<TSoftObjectPtr<UPaperFlipbook>>
		{
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Barracks/Building/1/Barracks1Open.Barracks1Open'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Barracks/Building/2/Barracks2Open.Barracks2Open'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Barracks/Building/3/Barracks3Open.Barracks3Open'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Barracks/Building/4/Barracks4Open.Barracks4Open'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Barracks/Building/5/Barracks5Open.Barracks5Open'"), NULL, LOAD_None, NULL)
		}
	}
};

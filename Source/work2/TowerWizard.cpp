// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerWizard.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Engine.h"

ATowerWizard::ATowerWizard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*if (!Initialized)
	{
		TArray<TSoftObjectPtr<UPaperFlipbook>> Idle;
		Idle.Add(LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/1/Magic1Idle.Magic1Idle'"), NULL, LOAD_None, NULL));
		Idle.Add(LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/2/Magic2Idle.Magic2Idle'"), NULL, LOAD_None, NULL));
		Idle.Add(LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/3/Magic3Idle.Magic3Idle'"), NULL, LOAD_None, NULL));
		Idle.Add(LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/4/Magic4Idle.Magic4Idle'"), NULL, LOAD_None, NULL));
		Idle.Add(LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/5/Magic5LDIdle.Magic5LDIdle'"), NULL, LOAD_None, NULL));

		TArray<TSoftObjectPtr<UPaperFlipbook>> Action;
		Action.Add(LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/1/Magic1Attack.Magic1Attack'"), NULL, LOAD_None, NULL));
		Action.Add(LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/2/Magic2Attack.Magic2Attack'"), NULL, LOAD_None, NULL));
		Action.Add(LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/3/Magic3Attack.Magic3Attack'"), NULL, LOAD_None, NULL));
		Action.Add(LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/4/Magic4Attack.Magic4Attack'"), NULL, LOAD_None, NULL));
		Action.Add(LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/5/Magic5LDAttack.Magic5LDAttack'"), NULL, LOAD_None, NULL));

		FlipbookMap.Add(ETowerState::TS_Idle,Idle);
		FlipbookMap.Add(ETowerState::TS_Action, Action);

		Initialized=true;
	}*/
}

TMap<uint8, float> ATowerWizard::TowerAttackRangeMap = {
{0,0},
{1,1400.0f},
{2,1400.0f},
{3,1400.0f},
{4,1400.0f},
{5,1400.0f},
{6,1400.0f}
};

TMap<uint8, float> ATowerWizard::TowerAttackSpeedMap = {
{0,0},
{1,1.5f},
{2,1.0f},
{3,1.5f},
{4,1.5f},
{5,1.5f},
{6,1.5f}
};

TMap<uint8, int32> ATowerWizard::TowerAttackDmgMap = {
{0,0},
{1,4},
{2,5},
{3,6},
{4,7},
{5,8},
{6,9}
};


TMap<ETowerState, TArray<TSoftObjectPtr<UPaperFlipbook>>> ATowerWizard::FlipbookMap =
{ 
	{	
		ETowerState ::TS_Idle ,TArray<TSoftObjectPtr<UPaperFlipbook>>
		{
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/1/Magic1Idle.Magic1Idle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/2/Magic2Idle.Magic2Idle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/3/Magic3Idle.Magic3Idle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/4/Magic4Idle.Magic4Idle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/5/Magic5LDIdle.Magic5LDIdle'"), NULL, LOAD_None, NULL)}	
		},
	{	
		ETowerState::TS_Action,TArray<TSoftObjectPtr<UPaperFlipbook>>
		{
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/1/Magic1Attack.Magic1Attack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/2/Magic2Attack.Magic2Attack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/3/Magic3Attack.Magic3Attack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/4/Magic4Attack.Magic4Attack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Magic/5/Magic5LDAttack.Magic5LDAttack'"), NULL, LOAD_None, NULL)
		}	
	}
};

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

inline float ATowerWizard::GetTowerRange() { return TowerAttackRangeMap[TowerTypeNum] + 0.0f; }
inline float ATowerWizard::GetTowerAttackSpd() { return TowerAttackSpeedMap[TowerTypeNum] + 0.0f; }
inline int32 ATowerWizard::GetTowerAttackDmg() { return TowerAttackDmgMap[TowerTypeNum] + 0; }

TSoftObjectPtr<UPaperFlipbook> ATowerWizard::GetFlipbookOfCurrentState()
{
	return ATowerWizard::FlipbookMap.Find(TowerState)->GetData()[TowerTypeNum - 1].Get();
}
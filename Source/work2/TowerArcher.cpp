// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerArcher.h"
#include "TowerEmpty.h"
#include "UITowerBase.h"
#include "MyUMGGameModeBase.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Engine.h"

ATowerArcher::ATowerArcher()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

TMap<uint8, float> ATowerArcher::TowerAttackRangeMap = {
{0,0},
{1,700.0f},
{2,700.0f},
{3,700.0f},
{4,700.0f},
{5,700.0f},
{6,700.0f}
};

TMap<uint8, float> ATowerArcher::TowerAttackSpeedMap = {
{0,0},
{1,0.8f},
{2,0.8f},
{3,0.8f},
{4,0.8f},
{5,0.8f},
{6,0.8f}
};

TMap<uint8, int32> ATowerArcher::TowerAttackDmgMap = {
{0,0},
{1,2},
{2,3},
{3,4},
{4,5},
{5,6},
{6,7}
};



inline FString ATowerArcher::GetPresetName()
{
	return "Archer";
}

FString ATowerArcher::GetTowerStatusText()
{
	return "TowerArcher Status Test";
}

FString ATowerArcher::GetTowerDescriptionText()
{
	return "TowerArcher Description Test";
}

inline float ATowerArcher::GetTowerRange() { return TowerAttackRangeMap[TowerTypeNum] + 0.0f; }
inline float ATowerArcher::GetTowerAttackSpd() { return TowerAttackSpeedMap[TowerTypeNum] + 0.0f;}
inline int32 ATowerArcher::GetTowerAttackDmg() { return TowerAttackDmgMap[TowerTypeNum] + 0;}

TSoftObjectPtr<UPaperFlipbook> ATowerArcher::GetFlipbookOfCurrentState()
{
	return ATowerArcher::FlipbookMap.Find(TowerState)->GetData()[(TowerTypeNum - 1)*4+(int)TowerDirectionState].Get();
}

TMap<ETowerState, TArray<TSoftObjectPtr<UPaperFlipbook>>> ATowerArcher::FlipbookMap =
{
	{
		ETowerState::TS_Idle ,TArray<TSoftObjectPtr<UPaperFlipbook>>
		{
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/1/Archer1LDIdle.Archer1LDIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/1/Archer1LTIdle.Archer1LTIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/1/Archer1RTIdle.Archer1RTIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/1/Archer1RDIdle.Archer1RDIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/2/Archer2LDIdle.Archer2LDIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/2/Archer2LTIdle.Archer2LTIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/2/Archer2RTIdle.Archer2RTIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/2/Archer2RDIdle.Archer2RDIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/NoUp/Archer3LDIdle.Archer3LDIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/NoUp/Archer3LTIdle.Archer3LTIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/NoUp/Archer3RTIdle.Archer3RTIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/NoUp/Archer3RDIdle.Archer3RDIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Upgraded/Archer3UpLDIdle.Archer3UpLDIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Upgraded/Archer3UpLTIdle.Archer3UpLTIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Upgraded/Archer3UpRTIdle.Archer3UpRTIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Upgraded/Archer3UpRDIdle.Archer3UpRDIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/4/Archer4LDIdle.Archer4LDIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/4/Archer4LTIdle.Archer4LTIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/4/Archer4RTIdle.Archer4RTIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/4/Archer4RDIdle.Archer4RDIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/5/Archer5LDIdle.Archer5LDIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/5/Archer5LTIdle.Archer5LTIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/5/Archer5RTIdle.Archer5RTIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/5/Archer5RDIdle.Archer5RDIdle'"), NULL, LOAD_None, NULL)
		}																																																		
		},
	{
		ETowerState::TS_Action,TArray<TSoftObjectPtr<UPaperFlipbook>>
		{
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/1/Archer1LDAttack.Archer1LDAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/1/Archer1LTAttack.Archer1LTAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/1/Archer1RTAttack.Archer1RTAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/1/Archer1RDAttack.Archer1RDAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/2/Archer2LDAttack.Archer2LDAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/2/Archer2LTAttack.Archer2LTAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/2/Archer2RTAttack.Archer2RTAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/2/Archer2RDAttack.Archer2RDAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/NoUp/Archer3LDAttack1.Archer3LDAttack1'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/NoUp/Archer3LTAttack1.Archer3LTAttack1'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/NoUp/Archer3RTAttack1.Archer3RTAttack1'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/NoUp/Archer3RDAttack1.Archer3RDAttack1'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Upgraded/Archer3UpLDAttack1.Archer3UpLDAttack1'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Upgraded/Archer3UpLTAttack1.Archer3UpLTAttack1'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Upgraded/Archer3UpRTAttack1.Archer3UpRTAttack1'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Upgraded/Archer3UpRDAttack1.Archer3UpRDAttack1'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/4/Archer4LDAttack.Archer4LDAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/4/Archer4LTAttack.Archer4LTAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/4/Archer4RTAttack.Archer4RTAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/4/Archer4RDAttack.Archer4RDAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/5/Archer5LDAttack.Archer5LDAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/5/Archer5LTAttack.Archer5LTAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/5/Archer5RTAttack.Archer5RTAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/5/Archer5RDAttack.Archer5RDAttack'"), NULL, LOAD_None, NULL)
		}
	}
};

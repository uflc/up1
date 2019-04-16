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

float ATowerArcher::TowerAttackRange = 350.0f;
float ATowerArcher::TowerAttackSpeed = 100.0f;
float ATowerArcher::TowerAttackDmg = 100.0f;

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

inline float ATowerArcher::GetTowerRange() { return ATowerArcher::TowerAttackRange+0.0f; }
inline float ATowerArcher::GetTowerAttackSpd() { return ATowerArcher::TowerAttackSpeed + 0.0f; }
inline float ATowerArcher::GetTowerAttackDmg() { return ATowerArcher::TowerAttackDmg + 0.0f; }

TSoftObjectPtr<UPaperFlipbook> ATowerArcher::GetFlipbookOfCurrentState()
{
	return ATowerArcher::FlipbookMap.Find(TowerState)->GetData()[(TowerTypeNum - 1)*4/* + Direction*/].Get();
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
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Archer3LDIdle.Archer3LDIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Archer3LTIdle.Archer3LTIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Archer3RTIdle.Archer3RTIdle'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Archer3RDIdle.Archer3RDIdle'"), NULL, LOAD_None, NULL),
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
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Archer3LDAttack.Archer3LDAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Archer3LTAttack.Archer3LTAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Archer3RTAttack.Archer3RTAttack'"), NULL, LOAD_None, NULL),
		LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Image/Tower/Archer/3/Archer3RDAttack.Archer3RDAttack'"), NULL, LOAD_None, NULL),
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

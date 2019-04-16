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


float ATowerWizard::TowerAttackRange = 700.0f;
float ATowerWizard::TowerAttackSpeed = 2.0f;
float ATowerWizard::TowerAttackDmg = 200.0f;

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

inline float ATowerWizard::GetTowerRange() { return ATowerWizard::TowerAttackRange + 0.0f; }
inline float ATowerWizard::GetTowerAttackSpd() { return ATowerWizard::TowerAttackSpeed + 0.0f; }
inline float ATowerWizard::GetTowerAttackDmg() { return ATowerWizard::TowerAttackDmg + 0.0f; }

TSoftObjectPtr<UPaperFlipbook> ATowerWizard::GetFlipbookOfCurrentState()
{
	return ATowerWizard::FlipbookMap.Find(TowerState)->GetData()[TowerTypeNum - 1].Get();
}
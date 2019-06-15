// Fill out your copyright notice in the Description page of Project Settings.

#include "TDGameModeBase.h"
#include "TDUnitCommonData.h"
#include "TowerDataTree.h"
#include "TDWeaponCommonData.h"
#include "Engine/AssetManager.h"
#include "TowerDefense.h"
#include "Kismet/GameplayStatics.h"
#include "TDPlayerController.h"

void ATDGameModeBase::LoadTDUnitCommons(const TArray<UTDUnitCommonData*>& InUsingTDUnitCommons)
{
	UnloadedTDUnitCommonNum = InUsingTDUnitCommons.Num();
	int AlreadyLoadedNum = 0;

	for (const auto& TDUnitCommon : InUsingTDUnitCommons)
	{
		if (TDUnitCommon->IsInitialzied())
		{
			UnloadedTDUnitCommonNum--;
			AlreadyLoadedNum++;
		}
		else
		{
			TDUnitCommon->OnFlipbooksLoaded.AddUObject(this, &ATDGameModeBase::OnTDUnitFlipbooksLoaded);
		}

		TDUnitCommon->Initialize();
	}
	//로드할 것이 없을 때 로드 완료
	if (AlreadyLoadedNum == InUsingTDUnitCommons.Num()) OnAllTDUnitFlipbooksLoaded.Broadcast();
}

void ATDGameModeBase::LoadTowerResources(UTowerData* InTowerDataTree)
{
	if (!InTowerDataTree) return;

	InTowerDataTree->Initialize();
	
	for (int i = 0; i < UPGRADES_NUM; i++)
	{
		LoadTowerResources(InTowerDataTree->GetNextUpgraded((ETowerType)i));
	}
}

//처음 로드된 것이 있을 때 전부 완료됬는지 체크.
void ATDGameModeBase::OnTDUnitFlipbooksLoaded()
{
	if (--UnloadedTDUnitCommonNum == 0)
	{
		OnAllTDUnitFlipbooksLoaded.Broadcast();
	}
}

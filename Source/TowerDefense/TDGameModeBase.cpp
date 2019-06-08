// Fill out your copyright notice in the Description page of Project Settings.

#include "TDGameModeBase.h"
#include "TDUnitCommonData.h"
#include "TowerDataTree.h"
#include "TDWeaponCommonData.h"
#include "Engine/AssetManager.h"
#include "TowerDefense.h"


void ATDGameModeBase::LoadTDUnitCommons(const TArray<UTDUnitCommonData*>& InUsingTDUnitCommons)
{
	UnloadedTDUnitCommonNum = InUsingTDUnitCommons.Num();
	int AlreadyLoadedNum = 0;

	for (const auto& TDUnitCommon : InUsingTDUnitCommons)
	{
		if (TDUnitCommon->IsInitialized)
		{
			UnloadedTDUnitCommonNum--;
			AlreadyLoadedNum++;
			continue;
		}
		
		TDUnitCommon->OnFlipbooksLoaded.BindUObject(this, &ATDGameModeBase::OnTDUnitFlipbooksLoaded);
		TDUnitCommon->Initialize();
	}

	//로드할 것이 없을 때 로드 완료
	if (AlreadyLoadedNum == InUsingTDUnitCommons.Num()) OnAllTDUnitFlipbooksLoaded.Broadcast();
}

void ATDGameModeBase::LoadTowerResources(UTowerData* InTowerDataTree)
{
	if (!InTowerDataTree) return;

	if (!InTowerDataTree->IsInitialized)
	{
		auto& AssetLoader = UAssetManager::GetStreamableManager();
		TArray<FSoftObjectPath> AssetsToLoad;

		for (const auto& UpType : InTowerDataTree->GetUpTypesInfo())
		{
			AssetsToLoad.AddUnique(UpType.UpPreview.ToSoftObjectPath());
		}
		for (const auto& Animation : InTowerDataTree->Animations)
		{
			AssetsToLoad.AddUnique(Animation.ToSoftObjectPath());
		}

		AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &ATDGameModeBase::LoadTowerResourcesDeffered));
		////
		InTowerDataTree->IsInitialized = true;
	}

	if (InTowerDataTree->WeaponData)
	{
		InTowerDataTree->WeaponData->Initialize();
	}
	
	for (int i = 0; i < 2; i++)
	{
		LoadTowerResources(InTowerDataTree->GetNextUpgraded((ETowerType)i));
	}
}

void ATDGameModeBase::LoadTowerResourcesDeffered()
{
	TD_LOG_CALLONLY(Warning);
}

//처음 로드된 것이 있을 때 전부 완료됬는지 체크.
void ATDGameModeBase::OnTDUnitFlipbooksLoaded()
{
	if (--UnloadedTDUnitCommonNum == 0)
	{
		OnAllTDUnitFlipbooksLoaded.Broadcast();
	}
}

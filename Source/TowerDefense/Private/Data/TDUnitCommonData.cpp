// Fill out your copyright notice in the Description page of Project Settings.


#include "TDUnitCommonData.h"
#include "TDWeaponCommonData.h"
#include "PaperFlipbook.h"
#include "Engine/AssetManager.h"
#include "TowerDefense.h"

UTDUnitCommonData::UTDUnitCommonData():IsInitialized(false)
{
}

void UTDUnitCommonData::Initialize()
{
	//if (IsInitialized) return; //하나만 따로 테스트 하는 경우 체크 필요. 실제로는 Iterate 하는 쪽에서 Bind 때문에 체크를 할 것이므로 불필요. 

	auto& AssetLoader = UAssetManager::GetStreamableManager();

	TArray<FSoftObjectPath> AssetsToLoad;
	for (auto& Animation : Animations)
	{
		AssetsToLoad.AddUnique(Animation.ToSoftObjectPath());
	}
	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDUnitCommonData::LoadFlipbooksDeffered));

	if(WeaponData)	WeaponData->Initialize();

//	IsInitialized = true;
}

void UTDUnitCommonData::LoadFlipbooksDeffered()
{
	for (auto& Animation : Animations)
	{
		if (!Animation.Get())
		{
			TD_LOG_CALLONLY(Warning);
			return;
		}
	}
	OnFlipbooksLoaded.ExecuteIfBound();
}

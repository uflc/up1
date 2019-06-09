// Fill out your copyright notice in the Description page of Project Settings.


#include "TDUnitCommonData.h"
#include "TDWeaponCommonData.h"
#include "PaperFlipbook.h"
#include "Engine/AssetManager.h"
#include "TowerDefense.h"
#include "TDUnit.h"

void UTDUnitCommonData::Initialize()
{
	if (!IsInitialized)
	{
		auto& AssetLoader = UAssetManager::GetStreamableManager();

		TArray<FSoftObjectPath> AssetsToLoad;
		for (const auto& Animation : Animations)
		{
			AssetsToLoad.AddUnique(Animation.ToSoftObjectPath());
		}
		for (const auto& Sound : Sounds)
		{
			AssetsToLoad.AddUnique(Sound.ToSoftObjectPath());
		}
		AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDUnitCommonData::LoadFlipbooksDeffered));
	}
	
	if (WeaponData)
	{
		WeaponData->Initialize();
	}
}

void UTDUnitCommonData::LoadFlipbooksDeffered()
{
	for (const auto& Animation : Animations)
	{
		if (!Animation.Get())
		{
			TD_LOG(Warning, TEXT("AsyncRquest done but the asset is still invalid!? This should never happen."));
			return;
		}
	}

	IsInitialized = true;
	OnFlipbooksLoaded.ExecuteIfBound();
}

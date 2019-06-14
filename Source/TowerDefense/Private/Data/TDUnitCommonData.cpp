// Fill out your copyright notice in the Description page of Project Settings.


#include "TDUnitCommonData.h"
#include "TDWeaponCommonData.h"
#include "PaperFlipbook.h"
#include "Sound/SoundCue.h"
#include "Engine/AssetManager.h"
#include "TowerDefense.h"
#include "TDUnit.h"

void UTDUnitCommonData::PostLoad()
{
	Super::PostLoad();

	bIsInitialized = false;
}

void UTDUnitCommonData::Initialize()
{
	if (!bIsInitialized)
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
		RealAnims.Add(Animation.Get());
	}

	for (const auto& Sound : Sounds)
	{
		if (!Sound.Get())
		{
			TD_LOG(Warning, TEXT("AsyncRquest done but the asset is still invalid!? This should never happen."));
			return;
		}
	}

	bIsInitialized = true;
	OnFlipbooksLoaded.Broadcast();
}

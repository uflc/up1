// Fill out your copyright notice in the Description page of Project Settings.


#include "TDProjectileCommonData.h"
#include "PaperFlipbook.h"
#include "Sound/SoundCue.h"
#include "Engine/AssetManager.h"
#include "TowerDefense.h"

void UTDProjectileCommonData::Initialize()
{
	if (!IsInitialized)
	{
		auto& AssetLoader = UAssetManager::GetStreamableManager();

		TArray<FSoftObjectPath> AssetsToLoad;
		for (const auto& it : FlipbookMap)
		{
			AssetsToLoad.AddUnique(it.Value.ToSoftObjectPath());
		}
		AssetsToLoad.AddUnique(HitSoundEffect.ToSoftObjectPath());
		AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDProjectileCommonData::LoadFlipbooksDeffered));
	}
}

void UTDProjectileCommonData::LoadFlipbooksDeffered()
{
	for (const auto& it : FlipbookMap)
	{
		if (!it.Value.Get())
		{
			TD_LOG(Warning, TEXT("AsyncRquest done but the asset is still invalid!? This should never happen."));
			return;
		}
	}

	if (!HitSoundEffect.Get())
	{
		TD_LOG(Warning, TEXT("AsyncRquest done but the asset is still invalid!? This should never happen."));
		return;
	}

	IsInitialized = true;
	OnFlipbooksLoaded.ExecuteIfBound();
}
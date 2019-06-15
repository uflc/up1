// Fill out your copyright notice in the Description page of Project Settings.


#include "TDProjectileCommonData.h"
#include "PaperFlipbook.h"
#include "Sound/SoundCue.h"
#include "Engine/AssetManager.h"
#include "TowerDefense.h"

void UTDProjectileCommonData::PostLoad()
{
	Super::PostLoad();

	bIsInitialized = false;
}

void UTDProjectileCommonData::Initialize()
{
	if (!bIsInitialized)
	{
		auto& AssetLoader = UAssetManager::GetStreamableManager();

		TArray<FSoftObjectPath> AssetsToLoad;
		for (const auto& it : FlipbookMap)
		{
			if (it.Value.IsPending())
			{
				AssetsToLoad.AddUnique(it.Value.ToSoftObjectPath());
			}
		}

		if (HitSound.IsPending())
		{
			AssetsToLoad.AddUnique(HitSound.ToSoftObjectPath());
		}

		if (AssetsToLoad.Num() > 0)
		{
			AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDProjectileCommonData::LoadFlipbooksDeffered));
		}
		else
		{
			LoadFlipbooksDeffered();
		}
	}
}

void UTDProjectileCommonData::LoadFlipbooksDeffered()
{
	for (const auto& it : FlipbookMap)
	{
		if (it.Value.IsPending())
		{
			TD_LOG(Warning, TEXT("AsyncRquest done but the asset is still invalid!"));
			return;
		}
	}

	if (HitSound.IsPending())
	{
		TD_LOG(Warning, TEXT("AsyncRquest done but the asset is still invalid!"));
		return;
	}

	bIsInitialized = true;
	OnFlipbooksLoaded.ExecuteIfBound();
}
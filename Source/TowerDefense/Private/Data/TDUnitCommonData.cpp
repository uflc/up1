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

void UTDUnitCommonData::LoadResources()
{
	if (!bIsInitialized)
	{
		auto& AssetLoader = UAssetManager::GetStreamableManager();

		TArray<FSoftObjectPath> AssetsToLoad;

		for (const auto& Animation : Animations)
		{
			if (Animation.IsPending())
			{
				AssetsToLoad.AddUnique(Animation.ToSoftObjectPath());
			}
		}

		for (const auto& Sound : Sounds)
		{
			if (Sound.IsPending())
			{
				AssetsToLoad.AddUnique(Sound.ToSoftObjectPath());
			}
		}

		if (AssetsToLoad.Num() > 0)
		{
			AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDUnitCommonData::LoadResourcesDeffered));
		}
		else
		{
			LoadResourcesDeffered();
		}
	}
	
	if (WeaponData)
	{
		WeaponData->LoadResources();
	}
}

void UTDUnitCommonData::LoadResourcesDeffered()
{
	for (const auto& Animation : Animations)
	{
		if (Animation.IsValid())
		{
			RealAnims.Add(Animation.Get());
		}
	}

	for (const auto& Sound : Sounds)
	{
		if (Sound.IsPending())
		{
			TD_LOG(Warning, TEXT("AsyncRquest done but %s is still invalid!"), *Sound.GetAssetName());
		}
	}

	bIsInitialized = true;
	OnLoadCompleted.Broadcast();
}

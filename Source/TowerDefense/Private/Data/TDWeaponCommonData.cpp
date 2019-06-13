// Fill out your copyright notice in the Description page of Project Settings.


#include "TDWeaponCommonData.h"
#include "TDProjectileCommonData.h"
#include "WeaponComponent.h"
#include "PaperFlipbook.h"
#include "Sound\SoundCue.h"
#include "Engine/AssetManager.h"
#include "TowerDefense.h"

void UTDWeaponCommonData::Initialize()
{
	if (!IsInitialized)
	{
		auto& AssetLoader = UAssetManager::GetStreamableManager();

		TArray<FSoftObjectPath> AssetsToLoad;
		AssetsToLoad.AddUnique(EffectFlipbook.ToSoftObjectPath());
		AssetsToLoad.AddUnique(FireSoundEffect.ToSoftObjectPath());
		AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDWeaponCommonData::LoadFlipbooksDeffered));
	}
	
	if (ProjectileData)
	{
		ProjectileData->Initialize();
	}
}

void UTDWeaponCommonData::LoadFlipbooksDeffered()
{
	if (!EffectFlipbook.Get() || !FireSoundEffect.Get())
	{
		TD_LOG(Warning, TEXT("AsyncRquest done but the asset is still invalid!? This should never happen."));
		return;
	}
	
	IsInitialized = true;
	OnFlipbooksLoaded.ExecuteIfBound();
}

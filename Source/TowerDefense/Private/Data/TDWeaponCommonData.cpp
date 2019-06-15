// Fill out your copyright notice in the Description page of Project Settings.


#include "TDWeaponCommonData.h"
#include "TDProjectileCommonData.h"
#include "WeaponComponent.h"
#include "PaperFlipbook.h"
#include "Sound\SoundCue.h"
#include "Engine/AssetManager.h"
#include "TowerDefense.h"

void UTDWeaponCommonData::PostLoad()
{
	Super::PostLoad();

	bIsInitialized = false;
}

void UTDWeaponCommonData::Initialize()
{
	if (!bIsInitialized)
	{
		auto& AssetLoader = UAssetManager::GetStreamableManager();

		TArray<FSoftObjectPath> AssetsToLoad;
		AssetsToLoad.AddUnique(HitFlipbook.ToSoftObjectPath());
		AssetsToLoad.AddUnique(AttackSound.ToSoftObjectPath());
		AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDWeaponCommonData::LoadFlipbooksDeffered));
	}
	
	if (ProjectileData)
	{
		ProjectileData->Initialize();
	}
}

void UTDWeaponCommonData::LoadFlipbooksDeffered()
{
	if (!HitFlipbook.Get() || !AttackSound.Get())
	{
		TD_LOG(Warning, TEXT("AsyncRquest done but the asset is still invalid"));
		return;
	}
	
	bIsInitialized = true;
	OnFlipbooksLoaded.ExecuteIfBound();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "TDWeaponCommonData.h"
#include "TDProjectileCommonData.h"
#include "WeaponComponent.h"
#include "PaperFlipbook.h"
#include "Sound\SoundCue.h"
#include "Engine/AssetManager.h"


void UTDWeaponCommonData::PostLoad()
{
	Super::PostLoad();

	bIsInitialized = false;
}

void UTDWeaponCommonData::LoadResources()
{
	if (!bIsInitialized)
	{
		auto& AssetLoader = UAssetManager::GetStreamableManager();

		TArray<FSoftObjectPath> AssetsToLoad;

		if (HitFlipbook.IsPending())
		{
			AssetsToLoad.AddUnique(HitFlipbook.ToSoftObjectPath());
		}

		if (AttackSound.IsPending())
		{
			AssetsToLoad.AddUnique(AttackSound.ToSoftObjectPath());
		}

		if (AssetsToLoad.Num() > 0)
		{
			AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDWeaponCommonData::LoadResourcesDeffered));
		}
		else
		{
			LoadResourcesDeffered();
		}
	}
	
	if (ProjectileData)
	{
		ProjectileData->LoadResources();
	}
}

void UTDWeaponCommonData::LoadResourcesDeffered()
{
	if (HitFlipbook.IsPending() 
	 || AttackSound.IsPending())
	{
		TD_LOG(Warning, TEXT("AsyncRquest done but the asset is still invalid"));
		return;
	}
	
	bIsInitialized = true;
	OnLoadCompleted.ExecuteIfBound();
}

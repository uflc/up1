// Fill out your copyright notice in the Description page of Project Settings.


#include "TDWeaponCommonData.h"
#include "TDProjectileCommonData.h"
#include "WeaponComponent.h"
#include "PaperFlipbook.h"
#include "Engine/AssetManager.h"


void UTDWeaponCommonData::Initialize()
{
	if (IsInitialized) return;

	auto& AssetLoader = UAssetManager::GetStreamableManager();

	TArray<FSoftObjectPath> AssetsToLoad;

	AssetsToLoad.AddUnique(EffectFlipbook.ToSoftObjectPath());

	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDWeaponCommonData::LoadFlipbooksDeffered));

	if (ProjectileData)
	{
		ProjectileData->Initialize();
	}

	IsInitialized = true;
}

void UTDWeaponCommonData::LoadFlipbooksDeffered()
{
	if (EffectFlipbook.Get())
	{
		OnFlipbooksLoaded.ExecuteIfBound();
	}
}

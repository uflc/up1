// Fill out your copyright notice in the Description page of Project Settings.


#include "TDWeaponCommonData.h"
#include "WeaponComponent.h"
#include "PaperFlipbook.h"
#include "Engine/AssetManager.h"
#include "Engine/World.h"

void UTDWeaponCommonData::Initialize()
{
	auto& AssetLoader = UAssetManager::GetStreamableManager();

	TArray<FSoftObjectPath> AssetsToLoad;

	AssetsToLoad.AddUnique(EffectFlipbook.ToSoftObjectPath());

	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDWeaponCommonData::LoadFlipbooksDeffered));
}

void UTDWeaponCommonData::LoadFlipbooksDeffered()
{
	if (EffectFlipbook) EffectFlipbook.Get();
	OnFlipbooksLoaded.ExecuteIfBound();
}

//inline UClass * UTDWeaponCommonData::GetWeaponClass() { return WeaponClass.Get(); }

// Fill out your copyright notice in the Description page of Project Settings.


#include "TDWeaponCommonData.h"

#include "PaperFlipbook.h"
#include "Runtime/Engine/Classes/Engine/AssetManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UTDWeaponCommonData::Initialize()
{
	auto& AssetLoader = UAssetManager::GetStreamableManager();

	TArray<FSoftObjectPath> AssetsToLoad;
	for (auto it : FlipbookMap)
	{
		AssetsToLoad.AddUnique(it.Value.ToSoftObjectPath());
	}
	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDWeaponCommonData::LoadFlipbooksDeffered));
}

void UTDWeaponCommonData::LoadFlipbooksDeffered()
{
	for (auto it : FlipbookMap)
	{
		TSoftObjectPtr<UPaperFlipbook> NewFlipbook = it.Value;
		if (NewFlipbook) NewFlipbook.Get();
	}
	OnFlipbooksLoaded.ExecuteIfBound();
}

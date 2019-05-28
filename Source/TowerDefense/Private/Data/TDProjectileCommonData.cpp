// Fill out your copyright notice in the Description page of Project Settings.


#include "TDProjectileCommonData.h"

#include "PaperFlipbook.h"
#include "Engine/AssetManager.h"
//#include "Runtime/Engine/Classes/Engine/World.h"

UTDProjectileCommonData::UTDProjectileCommonData():IsInitialized(false){}

void UTDProjectileCommonData::Initialize()
{
	if (IsInitialized) return;

	auto& AssetLoader = UAssetManager::GetStreamableManager();

	TArray<FSoftObjectPath> AssetsToLoad;
	for (auto& it : FlipbookMap)
	{
		AssetsToLoad.AddUnique(it.Value.ToSoftObjectPath());
	}
	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDProjectileCommonData::LoadFlipbooksDeffered));

	IsInitialized=true;
}

void UTDProjectileCommonData::LoadFlipbooksDeffered()
{
	for (auto& it : FlipbookMap)
	{
		TSoftObjectPtr<UPaperFlipbook> NewFlipbook = it.Value;
		if (NewFlipbook) NewFlipbook.Get();
	}
	OnFlipbooksLoaded.ExecuteIfBound();
}
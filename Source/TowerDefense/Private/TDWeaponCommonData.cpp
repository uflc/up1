// Fill out your copyright notice in the Description page of Project Settings.


#include "TDWeaponCommonData.h"

#include "PaperFlipbook.h"
#include "Runtime/Engine/Classes/Engine/AssetManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UTDWeaponCommonData::Initialize()
{
	auto& AssetLoader = UAssetManager::GetStreamableManager();

	TArray<FSoftObjectPath> AssetsToLoad;

	TSoftObjectPtr<UPaperFlipbook> NewFlipbook(EffectFlipbook);

	AssetsToLoad.AddUnique(NewFlipbook.ToSoftObjectPath());
	

	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDWeaponCommonData::LoadFlipbooksDeffered));

	IsInitialized = true;
}

void UTDWeaponCommonData::LoadFlipbooksDeffered()
{
	TSoftObjectPtr<UPaperFlipbook> NewFlipbook = EffectFlipbook;
	if (NewFlipbook) NewFlipbook.Get();
	OnFlipbooksLoaded.ExecuteIfBound();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPaperCharacterCommon.h"
#include "MyPaperCharacter.h"
#include "Runtime/Engine/Classes/Engine/AssetManager.h"

void UMyPaperCharacterCommon::LoadFlipbooksDeffered()
{
	for (auto it : FlipbookMap)
	{
		TSoftObjectPtr<UPaperFlipbook> NewFlipbook = it.Value;
		if (NewFlipbook) NewFlipbook.Get();
	}
}

void UMyPaperCharacterCommon::Initialize()
{
	auto& AssetLoader = UAssetManager::GetStreamableManager();

	TArray<FSoftObjectPath> AssetsToLoad;
	for (auto it : FlipbookMap)
	{
		AssetsToLoad.AddUnique(it.Value.ToSoftObjectPath());
	}
	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UMyPaperCharacterCommon::LoadFlipbooksDeffered));
}

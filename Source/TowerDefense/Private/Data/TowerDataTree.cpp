// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerDataTree.h"
#include "PaperFlipbook.h"
#include "Engine/AssetManager.h"
#include "TowerDefense.h"


void UTowerData::PostLoad()
{
	Super::PostLoad();

	bIsPreviewInitialized = false;
}

void UTowerData::Initialize()
{
	Super::Initialize();

	if (bIsPreviewInitialized) return;

	auto& AssetLoader = UAssetManager::GetStreamableManager();

	TArray<FSoftObjectPath> AssetsToLoad;

	for (const auto& UpType : UpTypes)
	{
		AssetsToLoad.AddUnique(UpType.UpPreview.ToSoftObjectPath());
	}

	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateLambda([this] () -> void
	{
		bIsPreviewInitialized = true;
	}));
}

UTowerData * UTowerData::GetNextUpgraded(const ETowerType & UpType)
{
	return UpTypes[(uint8)UpType].Upgrade;
}

UTowerData * UTowerData::GetUpgraded(const TArray<ETowerType>& UpTypeTree)
{
	UTowerData* Upgraded = this;

	for (const auto& UpType : UpTypeTree)
	{
		Upgraded = GetNextUpgraded(UpType);

		//Check if invaid UpType
		if (!Upgraded) break;
	}

	return Upgraded;
}

TArray<FTowerUpInfo>UTowerData::GetUpTypesInfo()
{
	return TArray<FTowerUpInfo>(UpTypes, UPGRADES_NUM);
}

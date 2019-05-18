// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerPreviewTextures.h"

UTextureArray * UTextureArray::UpgradeTo(const uint8 & EntryIdx, UPARAM(ref)TArray<TSoftObjectPtr<UTexture2D>>& OutArr)
{
	if (EntryIdx < 0 || EntryIdx > UPGRADABLE_NUM - 1) return nullptr;

	UTextureArray* Upgraded = Upgrades[EntryIdx];

	for (int i = 0; i < UPGRADABLE_NUM; i++)
		OutArr[i] = Upgraded->Entries[i];

	return Upgraded;
}

UTextureArray * UTextureArray::GetMatchingNode(const TArray<uint8>& UpTypes)
{
	auto Root = this;

	for (const auto& UpType : UpTypes)
	{
		//Invalid Indexing!
		if (UpType > UPGRADABLE_NUM - 1) return nullptr;

		//Check if Found Match
		if (!Root->Upgrades[UpType]) return Root;

		Root = Root->Upgrades[UpType];
	}
	return Root;
}

TArray<TSoftObjectPtr<UTexture2D>> UTextureArray::Get() const
{
	TArray<TSoftObjectPtr<UTexture2D>> OutEntries;

	for (int i = 0; i < UPGRADABLE_NUM; i++)
		OutEntries[i] = Entries[i];

	return OutEntries;
}

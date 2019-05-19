// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerUpDataTree.h"
#include "PaperFlipbook.h"

UTowerUpData * UTowerUpData::GetNextUpgraded(const ETowerType & UpType)
{
	//uint8 UpTypeByte = (uint8)UpType;

	//this should never happen
	//if (UpTypeByte > UPGRADES_NUM - 1) return nullptr;

	return Upgrades[(uint8)UpType];
}

UTowerUpData * UTowerUpData::GetUpgraded(const TArray<ETowerType>& UpTypes)
{
	auto Upgraded = this;

	for (const auto& UpType : UpTypes)
	{
		Upgraded = GetNextUpgraded(UpType);

		//Check if invaid UpType
		if (!Upgraded) break;
	}

	return Upgraded;
}

TArray<TSoftObjectPtr<UTexture2D>> UTowerUpData::GetUpPreviews()
{
	/*TArray<TSoftObjectPtr<UTexture2D>> OutEntries;

	for (int i = 0; i < UPGRADES_NUM; i++)
		OutEntries[i] = Upgrades[i];*/

	return TArray<TSoftObjectPtr<UTexture2D>>(UpPreviews, UPGRADES_NUM);
}

//@TODO UnitState is not safe!
UPaperFlipbook * UTowerUpData::GetMatchingAnim(const EDirection & Direction, const EUnitState & State)
{
	return Animations[((uint8) Direction) + ((uint8) State * 4/*EDirection::NumEnums*/)].Get();
}

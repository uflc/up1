// Fill out your copyright notice in the Description page of Project Settings.


#include "ProfTowerData.h"

FTalentInfo UProfTowerData::GetTalentInfo(const ETowerType & UpType) const
{
	return TalentsInfo[(uint8)UpType];
}

UDataAsset * UProfTowerData::GetTalentData(const ETowerType & UpType, const int32 TalentLevel)
{
	return TalentsInfo[(uint8)UpType].TalentData[TalentLevel];
}

ETalentType UProfTowerData::GetTalentType(const ETowerType & UpType)
{
	return TalentsInfo[(uint8)UpType].ClassType;
}

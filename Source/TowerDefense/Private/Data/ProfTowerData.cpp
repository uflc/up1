// Fill out your copyright notice in the Description page of Project Settings.


#include "ProfTowerData.h"
#include "TDWeaponCommonData.h"
#include "PassiveCommonData.h"

FTalentInfo UProfTowerData::GetTalentInfo(const ETowerType & UpType) const
{
	return TalentsInfo[(uint8)UpType];
}

UDataAsset * UProfTowerData::GetTalentData(const ETowerType & UpType, const int32 TalentLevel) const
{
	return TalentsInfo[(uint8)UpType].TalentData[TalentLevel];
}

int32 UProfTowerData::GetTalentCost(const ETowerType & UpType, const int32 TalentLevel) const
{
	return TalentsInfo[(uint8)UpType].Cost[TalentLevel];
}

ETalentType UProfTowerData::GetTalentType(const ETowerType & UpType) const
{
	return TalentsInfo[(uint8)UpType].ClassType;
}

void UProfTowerData::LoadResources()
{
	Super::LoadResources();

	for (auto Talent : TalentsInfo)
	{
		switch (Talent.ClassType)
		{
			case ETalentType::ActiveSkill:
			case ETalentType::Weapon:
				for(auto iTalentData : Talent.TalentData)
				{
					if(!iTalentData)
					{
						continue;
					}
					((UTDWeaponCommonData*)iTalentData)->LoadResources();
				}
			break;
			case ETalentType::PassiveSkill:
				for (auto iTalentData : Talent.TalentData)
				{
					if (!iTalentData) 
					{ 
						continue; 
					}
					((UPassiveCommonData*)iTalentData)->LoadResources();
				}
		}
	}
}

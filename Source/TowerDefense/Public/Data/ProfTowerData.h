// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDataTree.h"
#include "ProfTowerData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTalentInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Cost[TALENT_LEVEL_MAX];

	UPROPERTY(EditAnywhere)
	UDataAsset* TalentData[TALENT_LEVEL_MAX];

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETalentType ClassType; // Use Switch { Weapon / ActiveSkill / PassiveSkill }

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UActorComponent> Class;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Preview;
};

UCLASS(BlueprintType)
class TOWERDEFENSE_API UProfTowerData : public UTowerData
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	FTalentInfo TalentsInfo[UPGRADES_NUM];

	// For UI things
	UFUNCTION(BlueprintPure)
	FTalentInfo GetTalentInfo(const ETowerType& UpType) const;

	// Manually Cast 
	UFUNCTION(BlueprintPure)
	UDataAsset* GetTalentData(const ETowerType& UpType, const int32 TalentLevel);

	// Class infomation
	UFUNCTION(BlueprintPure)
	ETalentType GetTalentType(const ETowerType& UpType);

};

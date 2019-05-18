// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Tower.h"
#include "TowerPreviewTextures.generated.h"

#define UPGRADABLE_NUM 3

//@note TArray with FixedAlloc or c++ fixed array reference BP ¹ÌÁö¿ø
//@TODO make const?
UCLASS(BlueprintType)
class UTextureArray : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> Entries[UPGRADABLE_NUM];

	UPROPERTY(EditAnywhere)
	UTextureArray* Upgrades[UPGRADABLE_NUM];

public:
	UFUNCTION(BlueprintCallable)
	UTextureArray* UpgradeTo(const uint8 & EntryIdx, UPARAM(ref) TArray<TSoftObjectPtr<UTexture2D>>& OutArr);

	UFUNCTION(BlueprintCallable)
	UTextureArray* GetMatchingNode(const TArray<uint8>& UpTypes);
	

	/*UFUNCTION(BlueprintCallable)
	void GetCopy(UPARAM(ref) TArray<TSoftObjectPtr<UTexture2D>>& OutArr)
	{
		for (int i = 0; i < UPGRADABLE_NUM; i++)
			OutArr[i] = Entries[i];
	}*/

	UFUNCTION(BlueprintCallable)
	TArray<TSoftObjectPtr<UTexture2D>> Get() const;
};

/**
 * 
 */
UCLASS(BlueprintType)
class TOWERDEFENSE_API UTowerPreviewTextures : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TSubclassOf<ATower>, UTextureArray*> Entries;
};

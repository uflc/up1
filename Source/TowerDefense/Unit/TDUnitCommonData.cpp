// Fill out your copyright notice in the Description page of Project Settings.


#include "TDUnitCommonData.h"
//#include "TDUnit.h"
#include "Runtime/Engine/Classes/Engine/AssetManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TDGameModeBase.h"


void UTDUnitCommonData::Initialize()
{
	//if (IsInitialized) return; //하나만 따로 테스트 하는 경우 체크 필요. 실제로는 Iterate 하는 쪽에서 Bind 때문에 체크를 할 것이므로 불필요. 

	auto& AssetLoader = UAssetManager::GetStreamableManager();

	TArray<FSoftObjectPath> AssetsToLoad;
	for (auto it : FlipbookMap)
	{
		AssetsToLoad.AddUnique(it.Value.ToSoftObjectPath());
	}
	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDUnitCommonData::LoadFlipbooksDeffered));

	IsInitialized = true;
}

void UTDUnitCommonData::LoadFlipbooksDeffered()
{
	for (auto it : FlipbookMap)
	{
		TSoftObjectPtr<UPaperFlipbook> NewFlipbook = it.Value;
		if (NewFlipbook) NewFlipbook.Get();
	}
	OnFlipbooksLoaded.ExecuteIfBound();
}

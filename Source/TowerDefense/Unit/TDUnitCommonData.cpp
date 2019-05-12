// Fill out your copyright notice in the Description page of Project Settings.


#include "TDUnitCommonData.h"
//#include "TDUnit.h"
#include "Runtime/Engine/Classes/Engine/AssetManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TDGameModeBase.h"


void UTDUnitCommonData::Initialize()
{
	//if (IsInitialized) return; //�ϳ��� ���� �׽�Ʈ �ϴ� ��� üũ �ʿ�. �����δ� Iterate �ϴ� �ʿ��� Bind ������ üũ�� �� ���̹Ƿ� ���ʿ�. 

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

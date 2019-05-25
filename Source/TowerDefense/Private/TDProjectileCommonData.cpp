// Fill out your copyright notice in the Description page of Project Settings.


#include "TDProjectileCommonData.h"

#include "PaperFlipbook.h"
#include "Runtime/Engine/Classes/Engine/AssetManager.h"
//#include "Runtime/Engine/Classes/Engine/World.h"

void UTDProjectileCommonData::Initialize()
{
	//if (IsInitialized) return; //�ϳ��� ���� �׽�Ʈ �ϴ� ��� üũ �ʿ�. �����δ� Iterate �ϴ� �ʿ��� Bind ������ üũ�� �� ���̹Ƿ� ���ʿ�. 

	auto& AssetLoader = UAssetManager::GetStreamableManager();

	TArray<FSoftObjectPath> AssetsToLoad;
	for (auto it : FlipbookMap)
	{
		AssetsToLoad.AddUnique(it.Value.ToSoftObjectPath());
	}
	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDProjectileCommonData::LoadFlipbooksDeffered));
}

void UTDProjectileCommonData::LoadFlipbooksDeffered()
{
	for (auto it : FlipbookMap)
	{
		TSoftObjectPtr<UPaperFlipbook> NewFlipbook = it.Value;
		if (NewFlipbook) NewFlipbook.Get();
	}
	OnFlipbooksLoaded.ExecuteIfBound();
}
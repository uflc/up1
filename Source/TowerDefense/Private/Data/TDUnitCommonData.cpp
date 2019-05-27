// Fill out your copyright notice in the Description page of Project Settings.


#include "TDUnitCommonData.h"
#include "TDWeaponCommonData.h"
#include "PaperFlipbook.h"
#include "Engine/AssetManager.h"
#include "TowerDefense.h"

UTDUnitCommonData::UTDUnitCommonData():IsInitialized(false)
{
}

void UTDUnitCommonData::Initialize()
{
	//if (IsInitialized) return; //�ϳ��� ���� �׽�Ʈ �ϴ� ��� üũ �ʿ�. �����δ� Iterate �ϴ� �ʿ��� Bind ������ üũ�� �� ���̹Ƿ� ���ʿ�. 

	auto& AssetLoader = UAssetManager::GetStreamableManager();

	TArray<FSoftObjectPath> AssetsToLoad;
	for (auto& Animation : Animations)
	{
		AssetsToLoad.AddUnique(Animation.ToSoftObjectPath());
	}
	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UTDUnitCommonData::LoadFlipbooksDeffered));

	if(WeaponData)	WeaponData->Initialize();

//	IsInitialized = true;
}

void UTDUnitCommonData::LoadFlipbooksDeffered()
{
	for (auto& Animation : Animations)
	{
		if (!Animation.Get())
		{
			TD_LOG_CALLONLY(Warning);
			return;
		}
	}
	OnFlipbooksLoaded.ExecuteIfBound();
}

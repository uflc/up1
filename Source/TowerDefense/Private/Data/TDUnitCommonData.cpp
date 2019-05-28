// Fill out your copyright notice in the Description page of Project Settings.


#include "TDUnitCommonData.h"
#include "TDWeaponCommonData.h"
#include "PaperFlipbook.h"
#include "Engine/AssetManager.h"
#include "TowerDefense.h"
//#include "TDUnit.h"b

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

	IsInitialized = true;
	TD_LOG_CALLONLY(Warning);
	if (WeaponData)
	{
		WeaponData->Initialize();
	}

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
	//TD_LOG(Warning, TEXT("%s"), *GetOuter()->GetClass()->GetName());
	OnFlipbooksLoaded.ExecuteIfBound();
}

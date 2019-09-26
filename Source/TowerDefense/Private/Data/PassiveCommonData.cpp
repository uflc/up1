// Fill out your copyright notice in the Description page of Project Settings.


#include "PassiveCommonData.h"
#include "Sound\SoundCue.h"
#include "Engine/AssetManager.h"

void UPassiveCommonData::PostLoad()
{
	Super::PostLoad();

	bIsInitialized = false;
}

void UPassiveCommonData::LoadResources()
{
	if (!bIsInitialized)
	{
		auto& AssetLoader = UAssetManager::GetStreamableManager();

		TArray<FSoftObjectPath> AssetsToLoad;

		if (SoundEffect.IsPending())
		{
			AssetsToLoad.AddUnique(SoundEffect.ToSoftObjectPath());
		}

		if (AssetsToLoad.Num() > 0)
		{
			AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UPassiveCommonData::LoadResourcesDeffered));
		}
		else
		{
			LoadResourcesDeffered();
		}
	}

}

void UPassiveCommonData::LoadResourcesDeffered()
{
	if (SoundEffect.IsValid())
	{
		RealSoundEffect = SoundEffect.Get();
	}

	bIsInitialized = true;
	OnLoadCompleted.ExecuteIfBound();
}

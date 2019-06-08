// Fill out your copyright notice in the Description page of Project Settings.

#include "TDGameModeBase.h"
#include "TDUnitCommonData.h"
#include "TowerDataTree.h"
#include "TDPlayerController.h"//sea line 106
#include "HUDWidget.h"//sea line 106
#include "Engine/AssetManager.h"
#include "TowerDefense.h"
#include "TDWeaponCommonData.h"


void ATDGameModeBase::LoadTDUnitCommons(const TArray<UTDUnitCommonData*>& InUsingTDUnitCommons)
{
	UnloadedTDUnitCommonNum = InUsingTDUnitCommons.Num();
	int AlreadyLoadedNum = 0;

	for (const auto& TDUnitCommon : InUsingTDUnitCommons)
	{
		if (TDUnitCommon->IsInitialized)
		{
			UnloadedTDUnitCommonNum--;
			AlreadyLoadedNum++;
			continue;
		}
		
		TDUnitCommon->OnFlipbooksLoaded.BindUObject(this, &ATDGameModeBase::OnTDUnitFlipbooksLoaded);
		TDUnitCommon->Initialize();
	}

	//�ε��� ���� ���� �� �ε� �Ϸ�
	if (AlreadyLoadedNum == InUsingTDUnitCommons.Num()) OnAllTDUnitFlipbooksLoaded.Broadcast();
}

void ATDGameModeBase::LoadTowerResources(UTowerData* InTowerDataTree)
{
	if (!InTowerDataTree) return;

	if (!InTowerDataTree->IsInitialized)
	{
		auto& AssetLoader = UAssetManager::GetStreamableManager();
		TArray<FSoftObjectPath> AssetsToLoad;

		for (const auto& UpType : InTowerDataTree->GetUpTypesInfo())
		{
			AssetsToLoad.AddUnique(UpType.UpPreview.ToSoftObjectPath());
		}
		for (const auto& Animation : InTowerDataTree->Animations)
		{
			AssetsToLoad.AddUnique(Animation.ToSoftObjectPath());
		}

		AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &ATDGameModeBase::LoadTowerResourcesDeffered));
		////
		InTowerDataTree->IsInitialized = true;
	}

	if (InTowerDataTree->WeaponData)
	{
		InTowerDataTree->WeaponData->Initialize();
	}
	
	for (int i = 0; i < 2; i++)
	{
		LoadTowerResources(InTowerDataTree->GetNextUpgraded((ETowerType)i));
	}
}

void ATDGameModeBase::LoadTowerResourcesDeffered()
{
	TD_LOG_CALLONLY(Warning);
}

//ó�� �ε�� ���� ���� �� ���� �Ϸ����� üũ.
void ATDGameModeBase::OnTDUnitFlipbooksLoaded()
{
	if (--UnloadedTDUnitCommonNum == 0)
	{
		OnAllTDUnitFlipbooksLoaded.Broadcast();
	}
}


void ATDGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
		
		//@TODO move all UI stuff to ATDPlayerController?
		GetWorld()->GetFirstPlayerController<ATDPlayerController>()->HUDWidget = Cast<UHUDWidget>(CurrentWidget);
	}
}



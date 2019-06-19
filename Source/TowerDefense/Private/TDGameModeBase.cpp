// Fill out your copyright notice in the Description page of Project Settings.

#include "TDGameModeBase.h"
#include "TDUnitCommonData.h"
#include "TowerDataTree.h"
#include "TDWeaponCommonData.h"
#include "Engine/AssetManager.h"
#include "TowerDefense.h"
#include "Kismet/GameplayStatics.h"
#include "TDPlayerController.h"

void ATDGameModeBase::LoadTDUnitCommons(const TArray<UTDUnitCommonData*>& InUsingTDUnitCommons)
{
	UnloadedTDUnitCommonNum = InUsingTDUnitCommons.Num();
	int AlreadyLoadedNum = 0;

	for (const auto& TDUnitCommon : InUsingTDUnitCommons)
	{
		if (TDUnitCommon->IsInitialzied())
		{
			UnloadedTDUnitCommonNum--;
			AlreadyLoadedNum++;
		}
		else
		{
			TDUnitCommon->OnLoadCompleted.AddUObject(this, &ATDGameModeBase::OnTDUnitFlipbooksLoaded);
		}

		TDUnitCommon->LoadResources();
	}

	//�ε��� ���� ���� �� �Ϸ�.
	if (AlreadyLoadedNum == InUsingTDUnitCommons.Num())
	{
		OnAllTDUnitFlipbooksLoaded.Broadcast();
	}
}

void ATDGameModeBase::LoadTowerResources(UTowerData* BaseTowerData)
{
	if (!BaseTowerData) return;

	BaseTowerData->LoadResources();
	
	for (int i = 0; i < UPGRADES_NUM; i++)
	{
		LoadTowerResources(BaseTowerData->GetNextUpgraded((ETowerType)i));
	}
}

//Common�� �ε�� ������ ���� �Ϸ����� üũ.
void ATDGameModeBase::OnTDUnitFlipbooksLoaded()
{
	if (--UnloadedTDUnitCommonNum == 0)
	{
		OnAllTDUnitFlipbooksLoaded.Broadcast();
	}
}

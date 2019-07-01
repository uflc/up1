// Fill out your copyright notice in the Description page of Project Settings.

#include "TDGameModeBase.h"
#include "TDUnitCommonData.h"
#include "TowerDataTree.h"
#include "TDWeaponCommonData.h"
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

//Common�� �ε�� ������ ���� �Ϸ����� üũ.
void ATDGameModeBase::OnTDUnitFlipbooksLoaded()
{
	if (--UnloadedTDUnitCommonNum == 0)
	{
		OnAllTDUnitFlipbooksLoaded.Broadcast();
	}
}

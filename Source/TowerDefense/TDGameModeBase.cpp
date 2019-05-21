// Fill out your copyright notice in the Description page of Project Settings.

#include "TDGameModeBase.h"
#include "TDUnitCommonData.h"
#include "TowerUpDataTree.h"
#include "TDPlayerController.h"//
#include "HUDWidget.h"//
#include "Runtime/Engine/Classes/Engine/AssetManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TowerDefense.h"


UUserWidget * ATDGameModeBase::GetCurrentWidget()
{
	return CurrentWidget;
}

void ATDGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}


void ATDGameModeBase::LoadTDUnitCommons(UPARAM(ref) TArray<TSoftObjectPtr<UTDUnitCommonData>>& InUsingTDUnitCommons)
{
	UnloadedTDUnitCommonNum = InUsingTDUnitCommons.Num();
	int AlreadyLoadedNum = 0;

	for (auto& TDUnitCommon : InUsingTDUnitCommons)
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

	//로드할 것이 없을 때 로드 완료
	if (AlreadyLoadedNum == InUsingTDUnitCommons.Num()) OnAllTDUnitFlipbooksLoaded.Broadcast();
}

void ATDGameModeBase::LoadTowerResources(UTowerUpData * InTowerDataTree)
{
	if (!InTowerDataTree) return;

	auto& AssetLoader = UAssetManager::GetStreamableManager();
	TArray<FSoftObjectPath> AssetsToLoad;

	for (const auto& UpPreViewTex : InTowerDataTree->GetUpPreviews())
	{
		AssetsToLoad.AddUnique(UpPreViewTex.ToSoftObjectPath());
	}
	for (const auto& Animation : InTowerDataTree->Animations)
	{
		AssetsToLoad.AddUnique(Animation.ToSoftObjectPath());
	}

	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &ATDGameModeBase::LoadTowerResourcesDeffered));

	for (int i = 0; i < 2; i++)
	{
		LoadTowerResources(InTowerDataTree->GetNextUpgraded((ETowerType)i));
	}
}

void ATDGameModeBase::LoadTowerResourcesDeffered()
{
	TD_LOG_CALLONLY(Warning);
}

//처음 로드된 것들이 있을 때 사용할 모든 것들이 완료됬는지 체크.
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
		
		//@TODO move all UI stuff to ATDPlayerController
		GetWorld()->GetFirstLocalPlayerFromController<ATDPlayerController>()->HUDWidget = Cast<UHUDWidget>(CurrentWidget);
	}
}



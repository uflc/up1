// Fill out your copyright notice in the Description page of Project Settings.

#include "TDGameModeBase.h"
#include "Tower.h"
#include "TDUnit.h"
#include "TDUnitCommonData.h"
#include "TowerUpDataTree.h"


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

	//�ε��� ���� ���� �� �ε� �Ϸ�
	if (AlreadyLoadedNum == InUsingTDUnitCommons.Num()) OnAllTDUnitFlipbooksLoaded.Broadcast();
}

//ó�� �ε�� �͵��� ���� �� ����� ��� �͵��� �Ϸ����� üũ.
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
	}
}



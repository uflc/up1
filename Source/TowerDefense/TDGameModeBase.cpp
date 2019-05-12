// Fill out your copyright notice in the Description page of Project Settings.

#include "TDGameModeBase.h"
#include "Tower.h"
#include "TDUnit.h"
#include "TDUnitCommonData.h"


UUserWidget * ATDGameModeBase::GetCurrentWidget()
{
	return CurrentWidget;
}

void ATDGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);

}


void ATDGameModeBase::LoadTDUnitCommons(TArray<TSoftObjectPtr<UTDUnitCommonData>>& InUsingTDUnitCommons)
{
	int AlreadyLoadedNum = 0;

	for (auto TDUnitCommon : InUsingTDUnitCommons)
	{
		if (TDUnitCommon->IsInitialized)
		{
			AlreadyLoadedNum++;
			continue;
		}
		
		UnloadedTDUnitCommonNum++;

		TDUnitCommon->OnFlipbooksLoaded.BindUObject(this, &ATDGameModeBase::OnTDUnitFlipbooksLoaded);
		TDUnitCommon->Initialize();
	}

	//로드할 것이 없을 때 로드 완료
	if (AlreadyLoadedNum == InUsingTDUnitCommons.Num()) OnAllTDUnitFlipbooksLoaded.Broadcast();
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
	}
}



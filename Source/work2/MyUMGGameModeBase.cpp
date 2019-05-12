// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUMGGameModeBase.h"
#include "Tower.h"
#include "MyPaperCharacter.h"
#include "TDUnitCommonData.h"


UUserWidget * AMyUMGGameModeBase::GetCurrentWidget()
{
	return CurrentWidget;
}

void AMyUMGGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);

}


void AMyUMGGameModeBase::LoadTDUnitCommons(TArray<TSoftObjectPtr<UTDUnitCommonData>>& InUsingTDUnitCommons)
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

		TDUnitCommon->OnFlipbooksLoaded.BindUObject(this, &AMyUMGGameModeBase::OnTDUnitFlipbooksLoaded);
		TDUnitCommon->Initialize();
	}

	//�ε��� ���� ���� �� �ε� �Ϸ�
	if (AlreadyLoadedNum == InUsingTDUnitCommons.Num()) OnAllTDUnitFlipbooksLoaded.Broadcast();
}

//ó�� �ε�� �͵��� ���� �� ����� ��� �͵��� �Ϸ����� üũ.
void AMyUMGGameModeBase::OnTDUnitFlipbooksLoaded()
{
	if (--UnloadedTDUnitCommonNum == 0)
	{
		OnAllTDUnitFlipbooksLoaded.Broadcast();
	}
}


void AMyUMGGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
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



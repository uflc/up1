// Fill out your copyright notice in the Description page of Project Settings.

//#include "work2.h" //need?
#include "MyUMGGameModeBase.h"
#include "Tower.h"

UUserWidget * AMyUMGGameModeBase::GetCurrentWidget()
{
	return CurrentWidget;
}

//inline UUserWidget * AMyUMGGameModeBase::GetTowerWidget() { return TowerWidget; }

void AMyUMGGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
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

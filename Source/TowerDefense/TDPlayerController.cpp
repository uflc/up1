// Fill out your copyright notice in the Description page of Project Settings.

#include "TDPlayerController.h"
#include "HUDWidget.h"
#include "TDTypes.h"


void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();

			HUDWidget->UpdateValue(Coin, EValueType::Coin);
			HUDWidget->UpdateValue(Life, EValueType::Life);
			HUDWidget->UpdateValue(Mana, EValueType::Mana);
		}
	}
}

void ATDPlayerController::UpdateValue(int32 Value, EValueType Type)
{
	switch (Type)
	{
	case EValueType::Coin:
		Coin += Value;
		HUDWidget->UpdateValue(Coin, EValueType::Coin);
		break;
	case EValueType::Life:
		Life += Value;
		HUDWidget->UpdateValue(Life, EValueType::Life);
		break;
	case EValueType::Mana:
		Mana += Value;
		HUDWidget->UpdateValue(Mana, EValueType::Mana);
		break;
	default:
		return;
	}
}

void ATDPlayerController::ShowTowerActionMenu(ATower * InInteractingTower)
{
	if (!HUDWidget) return;

	HUDWidget->ShowTowerActionMenu(InInteractingTower);
}

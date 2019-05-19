// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"


/**
 * 
 UI Manager
 My~GameMode�� ����. TDGamePlayerController�� �����غ��� ��.
 */
UCLASS()
class TOWERDEFENSE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI|HUD")
	void ShowTowerActionMenu(ATower* InInteractingTower);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI|HUD")
	void HideTowerActionMenu();
};

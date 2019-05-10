// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "WidgetSwitcher.h" //�� ���� �߾��� ���� ���� �̻ܰŰ����� �𸣰���. 
#include "Tower.h"
#include "HUDWidget.generated.h"


/**
 * 
 UI Manager
 My~GameMode�� ����. TDGamePlayerController�� �����غ��� ��.
 */
UCLASS()
class WORK2_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	//UWidgetSwitcher TowerSelector;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|HUD")
	ATower* SelectedTower;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI|HUD")
	void ShowTowerActionMenu(ATower* InInteractingTower);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI|HUD")
	void HideTowerActionMenu();
};

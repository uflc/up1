// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "WidgetSwitcher.h" //이 위젯 잘쓰면 위젯 계층 이쁠거같은데 모르겟음. 
#include "Tower.h"
#include "HUDWidget.generated.h"


/**
 * 
 UI Manager
 My~GameMode가 소유. TDGamePlayerController도 생각해봐야 함.
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

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "TDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActionUnlockSignature, uint8);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "UI|HUD")
	class UHUDWidget* HUDWidget;

	UPROPERTY(EditAnywhere, Category = "UI|HUD")
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Coin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Life;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Mana;

	UPROPERTY(BlueprintReadOnly)
	ULevelData* LevelData;

	virtual void BeginPlay() override;

public:
	//@TODO ºÐ¸®, Health
	UFUNCTION(BlueprintCallable)
	void UpdateValue(int32 Value, EValueType Type);

	UFUNCTION(BlueprintCallable)
	void ApplyLevelData(ULevelData* InLevelData);

	UFUNCTION(BlueprintCallable, Category = "UI|Tower")
	void ShowTowerActionMenu(class ATower* InInteractingTower);	

	UFUNCTION(BlueprintCallable, Category = "UI|Tower")
	void HideTowerActionMenu();
};

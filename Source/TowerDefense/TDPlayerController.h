// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TDPlayer")
	int32 Coin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TDPlayer")
	int32 Life;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TDPlayer")
	int32 Mana;

	virtual void BeginPlay() override;

public:
	//@TODO ºÐ¸®, Health
	UFUNCTION(BlueprintCallable)
	void UpdateValue(int32 Value, EValueType Type);

	UFUNCTION(BlueprintCallable, Category = "UI|HUD")
	void ShowTowerActionMenu(class ATower* InInteractingTower);	

	UFUNCTION(BlueprintCallable, Category = "UI|HUD")
	void HideTowerActionMenu();
};

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

friend class ATDGameModeBase;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "UI|HUD")
	class UHUDWidget* HUDWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Property")
	int32 Coin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Property")
	int32 Life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Property")
	int32 Mana;

public:
	virtual void BeginPlay() override;

	//@TODO 분리, Health
	//@TODO 불필요한 콜스택 제거.
	UFUNCTION(BlueprintCallable)
	void UpdateValue(int32 Value, EValueType Type);

	UFUNCTION(BlueprintCallable, Category = "UI|HUD")
	void ShowTowerActionMenu(class ATower* InInteractingTower);
	
};

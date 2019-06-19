// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDUnit.h"
#include "Tower.generated.h"


UCLASS(Blueprintable)
class TOWERDEFENSE_API ATower : public ATDUnit
{
	GENERATED_BODY()
	
public:
	ATower();
	ATower(const FObjectInitializer& ObjectInitializer);

private:
	void InitializeDefaults();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsSelected;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalCost;

	virtual void BeginPlay() override;

public:	
	virtual void PostInitializeComponents() override;
	
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	UFUNCTION(BlueprintCallable, Category = "UI|HUD")
	void OnDeselected();

	UFUNCTION(BlueprintCallable, Category = "UI|HUD")
	void ShowActionMenu();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Tower")
	float GetTowerRange();
	virtual float GetTowerRange_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Tower")
	bool Upgrade(ETowerType UpType);
	virtual bool Upgrade_Implementation(ETowerType UpType);
};

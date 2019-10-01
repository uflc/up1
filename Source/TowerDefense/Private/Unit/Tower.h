// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TDUnit.h"
#include "TDTypes.h"
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

	int32 TalentLevel[UPGRADES_NUM];

	virtual void BeginPlay() override;

public:	
	virtual void PostInitializeComponents() override;
	
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	UFUNCTION(BlueprintCallable, Category = "UI|HUD")
	void OnDeselected();

	UFUNCTION(BlueprintCallable, Category = "UI|HUD")
	void ShowActionMenu();

	UFUNCTION(BlueprintPure, Category = "Tower")
	int32 GetTalentLevel(const ETowerType& UpType) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Tower")
	float GetTowerRange();
	virtual float GetTowerRange_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Upgrade(ETowerType UpType);
	virtual bool Upgrade_Implementation(ETowerType UpType);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool UpgradeTalent(ETowerType UpType);
	virtual bool UpgradeTalent_Implementation(ETowerType UpType);

	UFUNCTION(BlueprintCallable)
	bool IsTalentUpgradable(const ETowerType& UpType) const;

	UFUNCTION(BlueprintCallable)
	void UpdateTalentLevel(const ETowerType& UpType);
};

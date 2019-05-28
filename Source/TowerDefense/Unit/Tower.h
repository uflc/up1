// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDUnit.h"
#include "Tower.generated.h"


UCLASS(Abstract, BluePrintable)
class TOWERDEFENSE_API ATower : public ATDUnit
{
	GENERATED_BODY()
	
public:
	ATower();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsSelected;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsDelayChecking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalCost;

public:	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "UI|HUD")
	void OnDeselected();

	/*UFUNCTION(BlueprintCallable, Category = "UI|HUD|Tower")
	void OnSelected(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);*/

	UFUNCTION(BlueprintCallable, Category = "UI|HUD")
	void ShowActionMenu();

	virtual class UPaperFlipbook* GetDesiredAnimation() override;

	virtual bool UpdateAnimation() override;

	virtual void UpdateDirection() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TDUnit|Tower")
	bool Upgrade(ETowerType UpType);
	virtual bool Upgrade_Implementation(ETowerType UpType);

	////
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void StartAction();

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void ActionExecute();
};

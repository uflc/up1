// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDUnit.h"
#include "Tower.generated.h"


//@TODO disable movement
UCLASS(Abstract, BluePrintable)
class TOWERDEFENSE_API ATower : public ATDUnit
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSelected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTowerUpData* UpgradeTree;

public:	
	UFUNCTION(BlueprintCallable, Category = "UI|HUD|Tower")
	void OnDeselected();

	/*UFUNCTION(BlueprintCallable, Category = "UI|HUD|Tower")
	void OnSelected(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);*/

	UFUNCTION(BlueprintCallable, Category = "UI|HUD|Tower")
	void ShowActionMenu();

	//UFUNCTION()
	virtual class UPaperFlipbook* GetDesiredAnimation() override;

	//UFUNCTION(BlueprintCallable, Category = "TDUnit|Animation")
	virtual bool UpdateAnimation() override;

	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ResponseButtonEvent(int iNum);

	/*UFUNCTION(BlueprintCallable,BlueprintPure)
	virtual TSoftObjectPtr<class UPaperFlipbook> GetFlipbookOfCurrentState();*/
};

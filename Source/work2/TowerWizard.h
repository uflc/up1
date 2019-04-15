// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "TowerWizard.generated.h"

/**
 * 
 */
UCLASS()
class WORK2_API ATowerWizard : public ATower
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ATowerWizard();

protected:
	virtual void BeginPlay() override;

	// Actor OnClicked Signature delegate // this or blueprintimplementableevent?
	void Selected(AActor* TouchedActor, FKey ButtonPressed);

	////////////////////// UI ///////////////////////
	virtual void ShowActionMenu();
	virtual void HideActionMenu();

	static float TowerAttackRange;
	static float TowerAttackSpeed;
	static float TowerAttackDmg;
	static TMap<ETowerState, TArray<TSoftObjectPtr<UPaperFlipbook>>> FlipbookMap;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//virtual void ResponseButtonEvent(int iNum);
	virtual FString GetPresetName();

	virtual FString GetTowerStatusText();

	virtual FString GetTowerDescriptionText();

	virtual float GetTowerRange();
	virtual float GetTowerAttackSpd();
	virtual float GetTowerAttackDmg();
};

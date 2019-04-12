// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "TowerBarracks.generated.h"

/**
 * 
 */
UCLASS()
class WORK2_API ATowerBarracks : public ATower
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATowerBarracks();

protected:

	//Ÿ���� ������ ���׷��̵带 ���� �����ؼ� �׿� ���� ������ ������ ���
	//TArray<TSubclassOf<ATower>> Upgrades;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Actor OnClicked Signature delegate // this or blueprintimplementableevent?
	void Selected(AActor* TouchedActor, FKey ButtonPressed);

	////////////////////// UI ///////////////////////
	virtual void ShowActionMenu();
	virtual void HideActionMenu();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//virtual void ResponseButtonEvent(int iNum);
	virtual FString GetPresetName();

	virtual FString GetTowerStatusText();

	virtual FString GetTowerDescriptionText();

	virtual float GetTowerRange();
};
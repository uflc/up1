// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "TowerEmpty.generated.h"

/**
 * 
 */
UCLASS()
class WORK2_API ATowerEmpty : public ATower
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATowerEmpty();

protected:

	uint8 bIsActionMenuDisplayed : 1;

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
	virtual void ResponseButtonEvent(int iNum);
	virtual FString GetPresetName();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "TDGameModeBase.generated.h"

/**
 *���ҽ� �ε� �� ����� ���� ����
 *todo: ~~
 */
UCLASS()
class TOWERDEFENSE_API ATDGameModeBase : public AGameModeBase
{										
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFullyLoadedDelegate);

public:
	UPROPERTY(BlueprintAssignable, Category = "TDUnit")
	FFullyLoadedDelegate OnAllTDUnitFlipbooksLoaded;

protected:
	//TODO Config?
	//UPROPERTY(EditAnywhere, Category = "TDUnit")
	//TArray<class UTDUnitCommonData*> TDUnitCommons;

	//TODO �� ���� �ε� ���
	UFUNCTION(BlueprintCallable, Category = "TDUnit")
	void LoadTDUnitCommons(const TArray<UTDUnitCommonData*>& InUsingTDUnitCommons);

	int8 UnloadedTDUnitCommonNum;

	//BaseTowerData�κ��� ��� Ÿ�� �����Ϳ� ������ �� �ֱ� ������ �ϴ� �̷��� ��.
	UFUNCTION(BlueprintCallable, Category = "Tower")
	void LoadTowerResources(UTowerData* InTowerDataTree);

	void OnTDUnitFlipbooksLoaded();
};

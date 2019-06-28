// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "TDGameModeBase.generated.h"

/**
 *리소스 로드 및 사용할 위젯 관리
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

	//UPROPERTY(EditAnywhere, Category = "Tower")
	//UTowerData* BaseTowerData;

	//TODO 더 좋은 로딩 방법
	UFUNCTION(BlueprintCallable, Category = "TDUnit")
	void LoadTDUnitCommons(const TArray<UTDUnitCommonData*>& InUsingTDUnitCommons);

	int8 UnloadedTDUnitCommonNum;
	void OnTDUnitFlipbooksLoaded();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void StageComplete();
};

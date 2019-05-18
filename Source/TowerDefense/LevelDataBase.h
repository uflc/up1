// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include <utility>
#include "TDUnitCommonData.h"
#include "TDUnit.h"
#include "LevelDataBase.generated.h"


/**
 *
 ���� ���� �������� �� ������ Ư�� �� ������ ��ȯ�� ���̺긦 �����ϴ� ���� ����ü.
 */

USTRUCT(BlueprintType)
struct  FWaveData {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LocationIdx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATDUnit> UnitClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Delay;
};

USTRUCT(BlueprintType)
struct  FWaveDataArray{
	GENERATED_USTRUCT_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWaveData> Wave;
};


UCLASS(Blueprintable)
class TOWERDEFENSE_API ULevelDataBase : public UObject
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> Destination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> EnemyStartingLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWaveDataArray> LevelWaveArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> TowerLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDPlayer")
	int32 DefaultCoin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDPlayer")
	int32 DefaultLife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDPlayer")
	int32 DefaultMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDPlayer")
	int32 DefaultHeroHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSoftObjectPtr<UTDUnitCommonData>> UsingTDUnitCommons; //Get Class Defaults cannot hard reference
};

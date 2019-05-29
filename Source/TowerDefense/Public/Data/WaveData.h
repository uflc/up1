// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDCharacter.h"
#include "WaveData.generated.h"


/**
 *
 *레벨 마다 정해져야 할 정보와 특히 적 유닛이 소환될 웨이브를 구성하는 정보 구조체들.
 *각 레벨에는 웨이브의 스폰 위치 및 목적지를 보여주는 타겟 포인트 액터들을 만들고 각각 어레이로 AWaveSpawner::StartLevelWave()에 전달.
 */

/**
 *가장 작은 단위의 웨이브 정보. 
 *어떤 클래스로 언제부터 얼마만큼 어디서 어디로 어느 주기로 스폰 할지.
 */
USTRUCT(BlueprintType)
struct  FSubWaveData 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATDCharacter> SpawnUnitClass;

	UPROPERTY(EditAnywhere)
	uint8 SpawnLocationIdx;

	UPROPERTY(EditAnywhere)
	uint8 DestinationIdx;

	UPROPERTY(EditAnywhere)
	float StartingTime;

	UPROPERTY(EditAnywhere)
	uint8 Amount;

	UPROPERTY(EditAnywhere)
	float Delay;
};

USTRUCT(BlueprintType)
struct  FWaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FSubWaveData> Wave;
};

UCLASS(BlueprintType)
class TOWERDEFENSE_API ULevelWaveData : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TArray<FWaveData> WaveArray;

public:
	const TArray<FWaveData>& GetWaveArray() const { return WaveArray; }
};
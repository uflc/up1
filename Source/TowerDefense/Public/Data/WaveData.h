// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDCharacter.h"
#include "WaveData.generated.h"


/**
 *
 *���� ���� �������� �� ������ Ư�� �� ������ ��ȯ�� ���̺긦 �����ϴ� ���� ����ü��.
 *�� �������� ���̺��� ���� ��ġ �� �������� �����ִ� Ÿ�� ����Ʈ ���͵��� ����� ���� ��̷� AWaveSpawner::StartLevelWave()�� ����.
 */

/**
 *���� ���� ������ ���̺� ����. 
 *� Ŭ������ �������� �󸶸�ŭ ��� ���� ��� �ֱ�� ���� ����.
 */
USTRUCT(BlueprintType)
struct  FSubWaveData 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATDCharacter> SpawnUnitClass;

	UPROPERTY(EditAnywhere)
	uint8 SpawnLocationIdx;

	//���� �������� �бⰡ ���� ��, ������ �迭 �� �� ������ ����.
	UPROPERTY(EditAnywhere)
	TArray<uint8> DestBranchIdxQ;

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
	FORCEINLINE const TArray<FWaveData>& GetWaveArray() const { return WaveArray; }
};
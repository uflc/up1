// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "WaveSpawner.generated.h"

UCLASS(HideCategories=(Actor,Collision,Input))
class TOWERDEFENSE_API AWaveSpawner : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditInstanceOnly)
	class ULevelWaveData* LevelWaveData;

	uint8 WaveIdx;

	uint8 WaveLoopCount;

	uint32 SpawnedUnitNum;

	uint8 SubWaveRemaining;

	TArray<FTimerHandle> SubWaveTimerArr;
	TArray<uint8> SubWaveSpawnRemainingArr;
	bool bWaitingForFinishLevel;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* WaveStartSound;

	virtual void BeginPlay() override;

	void StartSubWaves();

	UFUNCTION()
	void NoticeUnitDestroyed(AActor* DestroyedActor);

	UFUNCTION()
	void SpawnSubWaveActor(const uint8 Index);

	const struct FSubWaveData& GetSubWaveData(const uint8 Index) const;

public:
	UFUNCTION(BlueprintCallable)
	void StartLevelWave(const TArray<AActor*>& InSpawnPoints);
};

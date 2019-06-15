// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveSpawner.generated.h"

UCLASS(HideCategories=(Actor,Collision,Input))
class TOWERDEFENSE_API AWaveSpawner : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TArray<class ATargetPoint*> SpawnPoints;

	UPROPERTY()
	TArray<class ATargetPoint*> Destinations;

	UPROPERTY(EditInstanceOnly)
	class ULevelWaveData* LevelWaveData;

	uint8 WaveIdx;

	//uint8 SubWaveIdx;
	//uint8 WaveSpawnRemaining;

	//FTimerHandle SubWaveTimer;
	//FTimerHandle SpawnTimer;

	uint32 SpawnedUnitNum;

	uint8 SubWaveRemaining;

	TArray<FTimerHandle> SubWaveTimerArr;
	TArray<uint8> SubWaveSpawnRemainingArr;
	bool bWaitingForFinishLevel;


protected:
	virtual void BeginPlay() override;

	void StartSubWaves();

	UFUNCTION()
	void NoticeUnitDestroyed(AActor* DestroyedActor);

	UFUNCTION()
	void SpawnSubWaveActor(const uint8 Index);

	const struct FSubWaveData& GetSubWaveData(const uint8 Index) const;

	//void StartSubWave();

	//void SetTimerToStartSubWave();

	//타이머에 의해 루프할 스폰 루틴. See StartSubWave()
	//void SpawnWaveActor();

	//const struct FSubWaveData& GetCurrentSubWaveData() const;

public:
	UFUNCTION(BlueprintCallable)
	void StartLevelWave(const TArray<class ATargetPoint*>& InSpawnPoints, const TArray<class ATargetPoint*>& InDestinations);
};

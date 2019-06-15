// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSpawner.h"
#include "WaveData.h"
#include "Engine/TargetPoint.h"
#include "TimerManager.h"
#include "TDAIController.h"
#include "TDCharacter.h"
#include "TowerDefense.h"

void AWaveSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (!LevelWaveData)
	{
		TD_LOG(Warning, TEXT("No LevelWaveData!"));
		Destroy();
	}
}

void AWaveSpawner::StartLevelWave(const TArray<ATargetPoint*>& InSpawnPoints, const TArray<ATargetPoint*>& InDestinations)
{
	if (InSpawnPoints.Num() == 0 || InDestinations.Num() == 0)
	{
		TD_LOG(Warning, TEXT("InSpawnPoints or InDestinations Array is Empty!"));
		return;
	}

	SpawnPoints = InSpawnPoints;
	Destinations = InDestinations;

	WaveIdx = 0;
	bWaitingForFinishLevel = false;

	StartSubWaves();
}

void AWaveSpawner::StartSubWaves()
{
	TD_LOG(Warning, TEXT("Start #%d Wave"), WaveIdx);

	const TArray<FSubWaveData>& SubWaves = LevelWaveData->GetWaveArray()[WaveIdx].Wave;

	uint8 SubWaveIndex = 0;

	SubWaveRemaining = SubWaves.Num();

	SubWaveSpawnRemainingArr.Empty();
	SubWaveTimerArr.Empty();

	for ( FSubWaveData SubWave : SubWaves )
	{
		if (SubWave.Amount <= 0
			|| !SpawnPoints.IsValidIndex(SubWave.SpawnLocationIdx)
			|| !Destinations.IsValidIndex(SubWave.DestinationIdx))
		{
			TD_LOG(Warning, TEXT("Invalid SpawnPoint or Destination or zero SpawnAmount! #%d Wave #%d Subwave"));
			return;
		}

		SubWaveSpawnRemainingArr.Add(SubWave.Amount);

		SubWaveTimerArr.Add(FTimerHandle());
		
		FTimerDelegate  TimerDelegate;
		TimerDelegate.BindUFunction(this, TEXT("SpawnSubWaveActor"), SubWaveIndex);

		GetWorldTimerManager().SetTimer(SubWaveTimerArr[SubWaveIndex++], TimerDelegate, SubWave.Delay != 0 ? SubWave.Delay : 0.01f, true, SubWave.StartingTime);
	}
}

void AWaveSpawner::NoticeUnitDestroyed(AActor* DestroyedActor)
{
	SpawnedUnitNum--;

	if (SpawnedUnitNum <= 0 && bWaitingForFinishLevel)
	{
		TD_LOG(Warning, TEXT("Next Level"));
		//todo like Gamemode->CompleteLevel;
	}
}


void AWaveSpawner::SpawnSubWaveActor(const uint8 Index)
{
	const FSubWaveData& SubWave = GetSubWaveData(Index);

	const FVector SpawnPoint = SpawnPoints[SubWave.SpawnLocationIdx]->GetActorLocation();
	const FVector Destination = Destinations[SubWave.DestinationIdx]->GetActorLocation();

	ATDCharacter* SpawnedUnit = (ATDCharacter*)GetWorld()->SpawnActor(SubWave.SpawnUnitClass, &SpawnPoint);
	SpawnedUnit->GetController<ATDAIController>()->SetDestination(Destination);

	SpawnedUnitNum++;
	SpawnedUnit->OnDestroyed.AddDynamic(this, &AWaveSpawner::NoticeUnitDestroyed);
	
	//SubWave의 끝 체크
	if (--(SubWaveSpawnRemainingArr[Index]) <= 0)
	{
		//현재 SubWave의 스폰 중지.
		GetWorldTimerManager().ClearTimer(SubWaveTimerArr[Index]);
		TD_LOG(Warning, TEXT("#%d SubWave Ended."), Index);

		//Is SubWave All Ends?
		if (--SubWaveRemaining <= 0)
		{
			TD_LOG(Warning, TEXT("#%d Wave Ended."), WaveIdx);

			const TArray<FWaveData>& WaveArray = LevelWaveData->GetWaveArray();
			//Level의 끝 체크.
			if (++WaveIdx > WaveArray.Num() - 1)
			{
				TD_LOG(Warning, TEXT("All Wave Ended."));

				bWaitingForFinishLevel = true;
				//루프 끝.
				return;
			}
			FTimerHandle NextWaveHandle;

			GetWorldTimerManager().SetTimer(NextWaveHandle, FTimerDelegate::CreateUObject(this, &AWaveSpawner::StartSubWaves),0.0f,false,5.0f);
		}
	}
}

const FSubWaveData & AWaveSpawner::GetSubWaveData(const uint8 Index) const
{
	return LevelWaveData->GetWaveArray()[WaveIdx].Wave[Index];
}

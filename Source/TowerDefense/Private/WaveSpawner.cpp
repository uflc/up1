// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSpawner.h"
#include "WaveData.h"
#include "Engine/TargetPoint.h"
#include "TimerManager.h"
#include "AIController.h"//
#include "BehaviorTree/BlackboardComponent.h"//
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

//todo safe?
const FSubWaveData& AWaveSpawner::GetCurrentSubWaveData() const
{
	return LevelWaveData->GetWaveArray()[WaveIdx].Wave[SubWaveIdx];
}

void AWaveSpawner::StartLevelWave(const TArray<ATargetPoint*>& InSpawnPoints, const TArray<ATargetPoint*>& InDestinations)
{
	SpawnPoints = InSpawnPoints;
	Destinations = InDestinations;

	//for (const auto& SpawnPoint : InSpawnPoints)
	//{
	//	SpawnPoints.Add(SpawnPoint->GetActorLocation());
	//	////SpawnPoint->Destroy();
	//}

	//for (const auto& Destination : InDestinations)
	//{
	//	Destinations.Add(Destination->GetActorLocation());
	//	////Destination->Destroy();
	//}

	WaveIdx = 0;
	SubWaveIdx = 0;

	SetTimerToStartSubWave();
}

void AWaveSpawner::StartSubWave()
{
	const FSubWaveData& SubWave = GetCurrentSubWaveData();
		
	if (SubWave.Amount <= 0) return;

	WaveSpawnRemaining = SubWave.Amount;

	GetWorldTimerManager().SetTimer(SpawnTimer, FTimerDelegate::CreateUObject(this, &AWaveSpawner::SpawnWaveActor), SubWave.Delay, true);
}

//todo safe!
void AWaveSpawner::SetTimerToStartSubWave()
{
	const float NextSubWaveDelay = GetCurrentSubWaveData().StartingTime;
	GetWorldTimerManager().SetTimer(SubWaveTimer, FTimerDelegate::CreateUObject(this, &AWaveSpawner::StartSubWave), NextSubWaveDelay, false);
}

void AWaveSpawner::SpawnWaveActor()
{
	const FSubWaveData& SubWave = GetCurrentSubWaveData();

	const FVector SpawnPoint = SpawnPoints[SubWave.SpawnLocationIdx]->GetActorLocation();
	const FVector Destination = Destinations[SubWave.DestinationIdx]->GetActorLocation();

	ATDCharacter* SpawnedUnit= (ATDCharacter*)GetWorld()->SpawnActor(SubWave.SpawnUnitClass, &SpawnPoint);
	//임시. todo 구현 AAIEnimyController->SetDestination(Destination);
	SpawnedUnit->GetController<AAIController>()->GetBlackboardComponent()->SetValueAsVector(FName(TEXT("Destination")), Destination);
	TD_LOG_CALLONLY(Warning);

	//SubWave의 끝 체크
	if (--WaveSpawnRemaining <= 0)
	{
		//현재 SubWave의 스폰 중지.
		GetWorldTimerManager().ClearTimer(SpawnTimer);
		TD_LOG(Warning, TEXT("#%d SubWave Ended."), SubWaveIdx);

		const TArray<FWaveData>& WaveArray = LevelWaveData->GetWaveArray();

		//Wave(Array of SubWave)의 끝 체크.
		if (++SubWaveIdx > WaveArray[WaveIdx].Wave.Num() - 1)
		{
			TD_LOG(Warning, TEXT("#%d Wave Ended."), WaveIdx);

			//Level의 끝 체크.
			if (++WaveIdx > WaveArray.Num() - 1)
			{
				TD_LOG(Warning, TEXT("All Wave Ended."));
				//루프 끝.
				return;
			}
			//다음 Wave에서 SubWave는 첫번째.
			SubWaveIdx = 0;
		}
		//다음 SubWave의 시작.
		SetTimerToStartSubWave();
	}
}

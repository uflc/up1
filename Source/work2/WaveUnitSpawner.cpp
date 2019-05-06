// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveUnitSpawner.h"
#include "Engine\World.h"
#include "Engine\Public\TimerManager.h"
#include "ParallelFor.h"
#include "Engine.h"
#include "MyPaperCharacter.h"

// Sets default values
AWaveUnitSpawner::AWaveUnitSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveUnitSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaveUnitSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaveUnitSpawner::Initialize(TArray<FWaveDataArray> iWaveData, TArray<FVector> iStartingLocation, TArray<FVector> iDestination)
{
	LevelWaveData=iWaveData;
	EnemyStartingLocation=iStartingLocation;
	EnemyDestination = iDestination;
}

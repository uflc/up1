// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveUnitSpawnerSub.h"
#include "WaveUnitSpawner.h"

// Sets default values
AWaveUnitSpawnerSub::AWaveUnitSpawnerSub()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveUnitSpawnerSub::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaveUnitSpawnerSub::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AWaveUnitSpawnerSub::Initialize(FWaveData iWaveData, TArray<FVector> iStartingLocation, TArray<FVector> iDestination, AWaveUnitSpawner* Root)
{
	LevelWaveData = iWaveData;
	EnemyStartingLocation = iStartingLocation;
	EnemyDestination = iDestination;
	RootSpawner=Root;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelDataBase.h"
#include "WaveUnitSpawner.generated.h"

UCLASS()
class WORK2_API AWaveUnitSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveUnitSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<FWaveDataArray> LevelWaveData;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<FVector> EnemyStartingLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FVector> EnemyDestination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ActiveSubSpawnerNumber;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Initialize(TArray<FWaveDataArray> iWaveData, TArray<FVector> iStartingLocation, TArray<FVector> iDestination);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void NthWaveSpawnExec(int32 idx);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void WaveSpawn();
};
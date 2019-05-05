// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelDataBase.h"
#include "WaveUnitSpawnerSub.generated.h"

class AWaveUnitSpawner;

UCLASS()
class WORK2_API AWaveUnitSpawnerSub : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveUnitSpawnerSub();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FWaveData LevelWaveData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FVector> EnemyStartingLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AWaveUnitSpawner* RootSpawner;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void WaveSpawnSub();

	UFUNCTION(BlueprintCallable)
	void Initialize(FWaveData iWaveData, TArray<FVector> iStartingLocation, AWaveUnitSpawner* Root);
};

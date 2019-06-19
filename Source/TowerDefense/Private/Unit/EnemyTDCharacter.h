// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/TDCharacter.h"
#include "EnemyTDCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AEnemyTDCharacter : public ATDCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyTDCharacter();
	
protected:
	// 웨이브 Destination에 도달 했을 때 플레이어에게 주는 피해량.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 LifeDamage;

	// 플레이어가 처치했을 때 얻는 현상금
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Bounty;

public:
	virtual void PostInitializeComponents() override;

	// 임시로 플레이어에게 처치 현상금을 주도록 함.
	virtual void Die_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual void Finish();
};

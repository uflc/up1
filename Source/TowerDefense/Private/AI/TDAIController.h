// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "AIController.h"
#include "TDAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	//ATDAIController(const FObjectInitializer& ObjectInitializer);
	
private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree*   BTAsset;

	UPROPERTY(EditAnywhere)
	class UBlackboardData* BBAsset;

	//Cache of Pawn as TDUnit
	UPROPERTY(VisibleAnywhere)
	class ATDUnit* TDUnit;

public:
	static const FName AggroTargetKey;
	static const FName AttackRangeKey;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void ReceiveWeaponChange();

	void SetAttackRange(const float AttackRange);

	class AActor* GetAggroTarget();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ATDUnit* GetTDUnit() const { return TDUnit; }

};

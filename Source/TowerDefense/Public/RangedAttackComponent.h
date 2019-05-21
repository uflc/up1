// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "RangedAttackComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API URangedAttackComponent : public UAttackComponent
{
	GENERATED_BODY()
	
protected:

	FVector ProjectileRelativeSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABulletBase> ProjectileClass;

	bool ProjectileisDirectable;

public:
	virtual void ExecAttack(class UObject* Target) override;

	UFUNCTION(BlueprintCallable)
	void Initialize(const FVector inVector,TSubclassOf<ABulletBase> inClass,bool inDirectable){
	ProjectileRelativeSpawnPoint=inVector; 
	ProjectileClass=inClass;
	ProjectileisDirectable= inDirectable;
	}
};

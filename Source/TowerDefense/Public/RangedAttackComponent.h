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
public:
	URangedAttackComponent();

protected:

	FVector ProjectileRelativeSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABulletBase> ProjectileClass;

	bool ProjectileisDirectable;

public:
<<<<<<< HEAD
	virtual void ExecAttack(class UObject* Target) override;

	UFUNCTION(BlueprintCallable)
	void Initialize(const FVector inVector,TSubclassOf<ABulletBase> inClass,bool inDirectable){
	ProjectileRelativeSpawnPoint=inVector; 
	ProjectileClass=inClass;
	ProjectileisDirectable= inDirectable;
	}
=======
	virtual void ExecAttack(class ATDCharacter* Target) override;

	virtual void Work() override;

	void Initialize() override;

	void Initialize(const FVector inVector, UClass* inClass, bool inDirectable);

	void Initialize(const float inRange, const FVector inVector, UClass* inClass, bool inDirectable);
>>>>>>> 9dbd6eed48176c0144435ed0a4729a740d1f2351
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDComponent.h"
#include "AttackComponent.generated.h"


UCLASS(Blueprintable, Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UAttackComponent : public UTDComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

protected:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SplashRange;

	//Need it for cache?
	//class ATDCharacter* Target;

public:	
	UFUNCTION(BlueprintCallable)
	virtual void Initialize();

	virtual void Initialize(const float inSplashRange);

	UFUNCTION(BlueprintCallable)
	virtual void ExecAttack(class ATDCharacter* Target){}
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectorComponent.h"
#include "TDTypes.h"
#include "DebufferComponent.generated.h"

class ATDCharacter;
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UDebufferComponent : public UEffectorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDebufferComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDebuffSet> DebuffSetArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DebuffChance;

public:	
	UFUNCTION(BlueprintCallable)
	void InitializeDebuffComp(float inEffectRange, const TArray<FDebuffSet>& inArr, float inChance);
	
	//virtual void Work() override;

	virtual void Effect(ATDCharacter* Target) override;
};

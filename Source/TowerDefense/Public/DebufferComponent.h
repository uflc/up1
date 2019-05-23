// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectorComponent.h"
#include "TDTypes.h"
#include "DebufferComponent.generated.h"


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EffectRange;

public:	
	UFUNCTION(BlueprintCallable)
	void InitializeDebuffComp(const TArray<FDebuffSet>& inArr, float inChance,float inEffectRange);
	
	virtual void Work() override;

	virtual void Affect(class ATDCharacter* Target) override;

};

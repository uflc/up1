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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDebuffSet> DebuffSetArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DebuffChance = 0;

public:	
	UFUNCTION(BlueprintCallable)
	void InitializeDebuffComp(float InEffectRange, const TArray<FDebuffSet>& InArr, float InChance);
	
	//virtual void Work() override;

	virtual void Effect(ATDCharacter* Target) override;
};

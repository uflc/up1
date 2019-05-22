// Fill out your copyright notice in the Description page of Project Settings.


#include "DebufferComponent.h"

// Sets default values for this component's properties
UDebufferComponent::UDebufferComponent():EffectRange(0)
{
}

inline void UDebufferComponent::Initialize(const TArray<FDebuffSet>& inArr, float inChance) {
	DebuffSetArray = inArr;
	DebuffChance = inChance;
}

void UDebufferComponent::Initialize(const TArray<FDebuffSet>& inArr, float inChance, float inEffectRange)
{
	UDebufferComponent::Initialize(inArr, inChance);
	EffectRange=inEffectRange;
}

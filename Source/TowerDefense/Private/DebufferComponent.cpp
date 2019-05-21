// Fill out your copyright notice in the Description page of Project Settings.


#include "DebufferComponent.h"

// Sets default values for this component's properties
UDebufferComponent::UDebufferComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

inline void UDebufferComponent::Initialize(const TArray<FDebuffSet>& inArr, float inChance, float inUsingRange) {
	DebuffSetArray = inArr;
	DebuffChance = inChance;
	UsingRange = inUsingRange;
	EffectRange = 0;
}

inline void UDebufferComponent::Initialize(const TArray<FDebuffSet>& inArr, float inChance, float inUsingRange, float inEffectRange) {
	DebuffSetArray = inArr;
	DebuffChance = inChance;
	UsingRange = inUsingRange;
	EffectRange = inEffectRange;
}

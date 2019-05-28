// Fill out your copyright notice in the Description page of Project Settings.


#include "DebufferComponent.h"

// Sets default values for this component's properties
UDebufferComponent::UDebufferComponent()
{
}

void UDebufferComponent::InitializeDebuffComp (float InEffectRange, const TArray<FDebuffSet>& Arr, float InChance)
{
	UEffectorComponent::InitializeEffectorComponent(InEffectRange);
	DebuffSetArray = Arr;
	DebuffChance = InChance;
	//EffectRange = inEffectRange;
}

void UDebufferComponent::Effect(ATDCharacter * Target)
{
	//Target->Debuff(~~);
}

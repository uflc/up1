// Fill out your copyright notice in the Description page of Project Settings.


#include "DebufferComponent.h"

// Sets default values for this component's properties
UDebufferComponent::UDebufferComponent()
{
}

void UDebufferComponent::InitializeDebuffComp (float iEffectRange, const TArray<FDebuffSet>& iArr, float iChance)
{
	UEffectorComponent::InitializeEffectorComponent(iEffectRange);
	DebuffSetArray = iArr;
	DebuffChance = iChance;
	//EffectRange = inEffectRange;
}

void UDebufferComponent::Effect(ATDCharacter * Target)
{
	//Target->Debuff(~~);
}

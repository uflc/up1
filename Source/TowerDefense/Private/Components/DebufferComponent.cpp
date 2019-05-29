// Fill out your copyright notice in the Description page of Project Settings.


#include "DebufferComponent.h"
#include "TDTypes.h"
#include "TDCharacter.h"
#include "GameFramework\FloatingPawnMovement.h"
#include "TDComponent.h"

void UDebufferComponent::InitializeDebuffComp (float InEffectRange, const TArray<FDebuffSet>& Arr, float InChance)
{
	UEffectorComponent::InitializeEffectorComponent(InEffectRange);
	DebuffSetArray = Arr;
	DebuffChance = InChance;
	//EffectRange = inEffectRange;
}

void UDebufferComponent::Effect(ATDCharacter * Target)
{
	// How can we setup Timers?


}

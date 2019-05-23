// Fill out your copyright notice in the Description page of Project Settings.


#include "DebufferComponent.h"

// Sets default values for this component's properties
UDebufferComponent::UDebufferComponent():EffectRange(0)
{
}

inline void UDebufferComponent::InitializeDebuffComp(const TArray<FDebuffSet>& inArr, float inChance =100.0f, float inEffectRange=0.0f)
{
	DebuffSetArray = inArr;
	DebuffChance = inChance;
	EffectRange=inEffectRange;
}

void UDebufferComponent::Work()
{
	// if (SplashRange > 0) SplashAffect(vTarget);

	// Affect(vTarget);
}

void UDebufferComponent::Affect(ATDCharacter * Target)
{
	//Target->Debuff(~~);

	//auto Arr = GetSubComponentsByClass(UEffectorComponent::StaticClass());

	//for (auto Effector : Arr)
	//{
	//	((UEffectorComponent*)Effector)->Affect(Target);
	//}
}

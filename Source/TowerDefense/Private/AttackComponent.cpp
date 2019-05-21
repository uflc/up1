// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "DebufferComponent.h"
//#include "TDUnit.h"


// Sets default values for this component's properties
UAttackComponent::UAttackComponent():SplashRange(0)
{
	PrimaryComponentTick.bCanEverTick = false;
}

inline void UAttackComponent::Initialize(const float inSplashRange) 
{
	if(SplashRange<0) return;

	SplashRange = inSplashRange;

	//auto SubComp = NewObject<UTDComponent>(this);

	//AddSubComponent(SubComp);
}

inline void UAttackComponent::Initialize() 
{
}

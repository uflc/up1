// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "DebufferComponent.h"
//#include "TDUnit.h"


// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SplashRange=0;
	// ...
}

inline void UAttackComponent::Initialize(const float inSplashRange) {
	SplashRange = inSplashRange;
	SetupDebuffers();
}

inline void UAttackComponent::Initialize() {
	SplashRange = 0;
	SetupDebuffers();
}

inline void UAttackComponent::SetupDebuffers() {
	for (auto DebufferClass : Debuffers)
	{
		auto DebufferComp = NewObject<UDebufferComponent>(this, DebufferClass.Get());
		SubComponents.Add(DebufferComp);
	}
}

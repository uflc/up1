// Fill out your copyright notice in the Description page of Project Settings.


#include "TDComponent.h"
#include "TDSubComponent.h"

// Sets default values for this component's properties
UTDComponent::UTDComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

inline void UTDComponent::AddSubComponent(UTDSubComponent * inComp) {
	inComp->SetParent(this);
	SubComponents.Add(inComp);
}

inline void UTDComponent::AddSubComponent(UClass * inClass) {
	//되는지 확인 못함.
	if (!inClass->IsChildOf<UTDSubComponent>()) return;
	auto SubComp = NewObject<UTDSubComponent>(this, inClass->GetClass());
	SubComp->SetParent(this);
	SubComponents.Add(SubComp);
}

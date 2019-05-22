// Fill out your copyright notice in the Description page of Project Settings.


#include "TDComponent.h"

// Sets default values for this component's properties
UTDComponent::UTDComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

inline void UTDComponent::AddSubComponent(UTDComponent * inComp) 
{
	inComp->SetParent(this);
	SubComponents.Add(inComp);
}

// Unused
inline void UTDComponent::AddSubComponent(UClass * inClass) 
{
	if (!inClass->IsChildOf<UTDComponent>()) return;
	auto SubComp = NewObject<UTDComponent>(this, inClass->GetClass());
	SubComp->SetParent(this);
	SubComponents.Add(SubComp);
}

UTDComponent * UTDComponent::FindSubComponent(const TSubclassOf<UActorComponent> ComponentClass) const
{
	UTDComponent* FoundComponent = nullptr;

	if (UClass* TargetClass = ComponentClass.Get())
	{
		for (UTDComponent* Component : SubComponents)
		{
			if (Component && Component->IsA(TargetClass))
			{
				FoundComponent = Component;
				break;
			}
		}
	}

	return FoundComponent;
}

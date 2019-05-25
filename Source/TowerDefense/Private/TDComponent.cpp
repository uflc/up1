// Fill out your copyright notice in the Description page of Project Settings.


#include "TDComponent.h"

// Sets default values for this component's properties
UTDComponent::UTDComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

//inline void UTDComponent::AddSubComponent(UTDComponent * inComp) 
//{
//	inComp->SetParent(this);
//	SubComponents.Add(inComp);
//}

inline UTDComponent * UTDComponent::GetSubComponent(const TSubclassOf<UTDComponent> ComponentClass) const
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

inline TArray<UTDComponent*> UTDComponent::GetSubComponentsByClass(TSubclassOf<UTDComponent> ComponentClass) const
{
	TArray<UTDComponent*> ValidComponents;

	// In the UActorComponent case we can skip the IsA checks for a slight performance benefit
	if (ComponentClass == UTDComponent::StaticClass())
	{
		for (UTDComponent* Component : SubComponents)
		{
			if (Component)
			{
				ValidComponents.Add(Component);
			}
		}
	}
	else if (*ComponentClass)
	{
		for (UTDComponent* Component : SubComponents)
		{
			if (Component && Component->IsA(ComponentClass))
			{
				ValidComponents.Add(Component);
			}
		}
	}

	return ValidComponents;
}


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

	//*UFloatingPawnMovement* Movement;
	//TArray<UActorComponent*> TDComponentArray;
	//
	//if (Target->IsValidLowLevel()&& Target->GetMovementComponent()->IsValidLowLevel())
	//{
	//	Movement = Cast<UFloatingPawnMovement>(Target->GetMovementComponent());
	//}

	//for (FDebuffSet DebuffInfo : DebuffSetArray)
	//{
	//	EDebuffType Type=DebuffInfo.Type;
	//	switch (Type) 
	//	{
	//		case EDebuffType::Slow:
	//			if (Movement)
	//			{
	//				Movement->MaxSpeed *= (DebuffInfo.Power / 100.0f);
	//			}
	//			break;

	//		case EDebuffType::Snared:
	//			if (Movement)
	//			{
	//				Movement->MaxSpeed = 0;
	//			}
	//			break;

	//		case EDebuffType::Stun:
	//			if (Movement)
	//			{
	//				Movement->MaxSpeed = 0;
	//			}

	//			TDComponentArray = Target->GetComponentsByClass(UTDComponent::StaticClass());

	//			for(UActorComponent* Comp : TDComponentArray)
	//			{
	//				(UTDComponent*)Comp->Deactivate();
	//			}
	//			break;

	//		default:
	//			return;
	//	}
	//}*/
}

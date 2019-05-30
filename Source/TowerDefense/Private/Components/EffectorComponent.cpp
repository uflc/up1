// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectorComponent.h"
#include "WorldCollision.h"
#include "TDCharacter.h"


void UEffectorComponent::InitializeEffectorComponent(float InEffectRange)
{
	EffectRange = InEffectRange;
}

void UEffectorComponent::AffectTarget(ATDCharacter* MainTarget)
{
	const FVector TargetLocation = MainTarget->GetActorLocation();
	const EUnitTeam TargetTeam = MainTarget->Team;

	if (EffectRange > 0)
	{
		TArray<FHitResult> OutResults;

		//FCollisionQueryParams QueryParam;
		//QueryParam.AddIgnoredActor(MainTarget);

		GetWorld()->SweepMultiByChannel(OutResults, TargetLocation, (TargetLocation + FVector(0, 0, 0.1f)), FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(EffectRange)/*, QueryParam*/);

		for (const auto& HitResult : OutResults)
		{
			ATDCharacter* HitTDCharacter = Cast<ATDCharacter>(HitResult.Actor.Get());
			if (!HitTDCharacter) continue;

			if (HitTDCharacter->Team == TargetTeam)
			{
				Effect(HitTDCharacter);
			}
		}
	}
	else
	{
		Effect(MainTarget);
	}
}

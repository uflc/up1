// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectorComponent.h"
#include "WorldCollision.h"
#include "TDCharacter.h"


void UEffectorComponent::InflictEffect(ATDCharacter* Target)
{
	if (!Target) return;

	static const float ShakePower = 4.0f;
	static const float ShakeDuration = 0.2f;
	Target->TDUnitTakeDamage(ShakePower, ShakeDuration, Damage);

	for ( FDebuff Debuff : Debuffs )
	{
		Target->TDUnitTakeDebuff(Debuff);
	}
	//todo InflictDebuff and fun gameplay logic
}

void UEffectorComponent::Initialize(float InEffectRange, uint32 InDamage)
{
	EffectRange = InEffectRange;
	Damage		= InDamage;
}

void UEffectorComponent::Initialize(const TArray<FDebuff>& InDebuffArray)
{
	Debuffs = InDebuffArray;
}

void UEffectorComponent::InflictAoE(ATDCharacter* MainTarget)
{
	if (!MainTarget) return;

	const FVector TargetLocation = MainTarget->GetActorLocation();
	const EUnitTeam TargetTeam	 = MainTarget->Team;

	static const FVector SweepDistance = FVector(0, 0, 0.1f);

	if (EffectRange > 0)
	{
		TArray<FHitResult> OutResults;
		GetWorld()->SweepMultiByChannel(OutResults, TargetLocation, (TargetLocation + SweepDistance), FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(EffectRange)/*, QueryParam*/);
		for (const auto& HitResult : OutResults)
		{
			ATDCharacter* HitTDCharacter = Cast<ATDCharacter>(HitResult.Actor.Get());

			if (HitTDCharacter && HitTDCharacter->Team == TargetTeam)
			{
				InflictEffect(HitTDCharacter);
			}
		}
	}
	else
	{
		InflictEffect(MainTarget);
	}
}

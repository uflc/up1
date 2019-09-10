// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectorComponent.h"
#include "TDCharacter.h"


void UEffectorComponent::InflictEffect(ATDCharacter* Target)
{
	if (!Target) return;

	static const float ShakePower			= 4.0f;
	static const float ShakeDuration	= 0.2f;

	FDamage DamageToApp;
	DamageToApp.Damage			=	Damage;
	DamageToApp.DebuffArray	= Debuffs;

	Target->TDUnitTakeDamage(DamageToApp);
}

void UEffectorComponent::Initialize(float InEffectRange, uint32 InDamage, const TArray<FDebuff>& InDebuffArray)
{
	EffectRange = InEffectRange;
	Damage		= InDamage;
	Debuffs     = InDebuffArray;
}

void UEffectorComponent::InflictAoE(ATDCharacter* MainTarget)
{
	if (!MainTarget) return;

	const FVector TargetLocation = MainTarget->GetActorLocation();
	const EUnitTeam TargetTeam	 = MainTarget->GetTeam();

	static const FVector SweepDistance = FVector(0, 0, 0.1f);

	if (EffectRange > 0)
	{
		TArray<FHitResult> OutResults;
		GetWorld()->SweepMultiByChannel(OutResults, TargetLocation, (TargetLocation + SweepDistance), FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(EffectRange)/*, QueryParam*/);
		for (const auto& HitResult : OutResults)
		{
			ATDCharacter* HitTDCharacter = Cast<ATDCharacter>(HitResult.Actor.Get());

			if (HitTDCharacter && HitTDCharacter->GetTeam() == TargetTeam)
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

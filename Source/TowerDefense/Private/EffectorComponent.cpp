// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectorComponent.h"
#include "WorldCollision.h"
#include "TDCharacter.h"

UEffectorComponent::UEffectorComponent():vTarget(nullptr), AffectRange(0)
{

}

void UEffectorComponent::SplashAffect()
{
	SplashAffect(vTarget);
}

void UEffectorComponent::SplashAffect(const ATDCharacter * MainTarget)
{
	FVector TargetLocation = (MainTarget)->GetActorLocation();
	auto TargetTeam = MainTarget->Team;

	TArray<FHitResult> OutResults;

	FCollisionQueryParams QueryParam;
	QueryParam.AddIgnoredActor(MainTarget);

	GetWorld()->SweepMultiByChannel(OutResults, TargetLocation, (TargetLocation + FVector(0, 0, 0.1f)), FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(AffectRange), QueryParam);

	for (auto HitResult : OutResults)
	{
		ATDCharacter* HitTDCharacter = Cast<ATDCharacter>(/*HitActor*/HitResult.Actor.Get());
		if (!HitTDCharacter)continue;

		if (HitTDCharacter->Team == TargetTeam)
			Affect(HitTDCharacter);
	}
}

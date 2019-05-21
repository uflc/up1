// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttackComponent.h"
#include "TDCharacter.h"
#include "SimpleFlipbookEffect.h"

#include "WorldCollision.h"
#include "Engine\World.h"
#include "Engine\Classes\Engine\EngineTypes.h"

inline void UMeleeAttackComponent::Initialize()
{
	Super::Initialize();
	EffectFlipbook = nullptr;
}

inline void UMeleeAttackComponent::Initialize(const float inSplashRange, UPaperFlipbook * inEffectFlipbook) {
	Super::Initialize(inSplashRange);
	EffectFlipbook = inEffectFlipbook;
}

void UMeleeAttackComponent::ExecAttack(ATDCharacter* Target)
{

	if(Target->IsValidLowLevelFast() && GetOwner()->IsValidLowLevelFast()){
		FVector TargetLocation=(Target)->GetActorLocation();
		auto TargetTeam = Target->Team;

		(GetWorld()->SpawnActor<ASimpleFlipbookEffect>(TargetLocation, FRotator()))->SetupEffect(EffectFlipbook);


		//SetAffect(&ATDCharacter::TDUnitTakeDamage);

		TArray<FHitResult> OutResults;

		FCollisionQueryParams QueryParam;
		QueryParam.AddIgnoredActor(Target);

		GetWorld()->SweepMultiByChannel(OutResults, TargetLocation, (TargetLocation+FVector(0,0,0.1f)), FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(SplashRange),QueryParam);

		for (auto HitResult : OutResults)
		{
			//AActor* HitActor= HitResult.Actor.Get();
			//if(!HitActor->IsValidLowLevelFast())continue;

			ATDCharacter* HitTDCharacter= Cast<ATDCharacter>(/*HitActor*/HitResult.Actor.Get());
			if(!HitTDCharacter)continue;

			if(HitTDCharacter->Team==TargetTeam)
			HitTDCharacter->TDUnitTakeDamage(5.0f, 0.2f, ((ATDUnit*)GetOwner())->AttackDamage*0.5f);
			//CallAffect(HitTDCharacter,Params);
		}

		Target->TDUnitTakeDamage(10.0f,0.2f,((ATDUnit*)GetOwner())->AttackDamage);
	}
}
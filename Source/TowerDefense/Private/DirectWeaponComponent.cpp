// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectWeaponComponent.h"
#include "TDCharacter.h"
#include "SimpleFlipbookEffect.h"
#include "EffectorComponent.h"

UDirectWeaponComponent::UDirectWeaponComponent():EffectFlipbook(nullptr)
{

}


inline void UDirectWeaponComponent::InitializeDirectAttackComp() {
	UWeaponComponent::InitializeWeaponComp();

	// Additional Work
}

void UDirectWeaponComponent::ExecAttack(ATDCharacter* Target)
{
	if(Target->IsValidLowLevelFast() && GetOwner()->IsValidLowLevelFast()){
		Target->TDUnitTakeDamage(10.0f,0.2f,((ATDUnit*)GetOwner())->AttackDamage);
	}
}

// Have to test
void UDirectWeaponComponent::UseWeapon()
{	
	// Gonna change to using common data

	if (TargetValidCheck()) {

		if(EffectFlipbook)		(GetWorld()->SpawnActor<ASimpleFlipbookEffect>(vTarget->GetActorLocation(), FRotator()))->SetupEffect(EffectFlipbook);

		auto Arr = GetSubComponentsByClass(UEffectorComponent::StaticClass());

		for (auto Effector : Arr)
		{
			((UEffectorComponent*)Effector)->AffectTarget(vTarget);
		}
	}
}
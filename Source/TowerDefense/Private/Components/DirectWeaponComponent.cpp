// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectWeaponComponent.h"
#include "TDCharacter.h"
#include "SimpleFlipbookEffect.h"
#include "EffectorComponent.h"

UDirectWeaponComponent::UDirectWeaponComponent():EffectFlipbook(nullptr)
{

}


//inline void UDirectWeaponComponent::InitializeDirectWeaponComp() {
//	UWeaponComponent::InitializeWeaponComp();
//
//	// Additional Work
//}

// Have to test
void UDirectWeaponComponent::UseWeapon()
{	
	// Gonna change to using common data

	if (TargetValidCheck()) 
	{
		if (EffectFlipbook)		(GetWorld()->SpawnActor<ASimpleFlipbookEffect>(vTarget->GetActorLocation(), FRotator()))->SetupEffect(EffectFlipbook);

		TArray<UTDComponent*> Effectors = GetSubComponentsByClass(UEffectorComponent::StaticClass());

		for (auto& Effector : Effectors)
		{
			((UEffectorComponent*)Effector)->AffectTarget(vTarget);
		}
	}
}
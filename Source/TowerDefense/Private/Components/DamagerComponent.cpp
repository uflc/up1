// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagerComponent.h"
#include "TDCharacter.h"

void UDamagerComponent::Effect(ATDCharacter* Target)
{
	const float DefaultShakePower= 4.0f;
	const float DefaultShakeDuration= 0.2f;
	Target->TDUnitTakeDamage(DefaultShakePower,DefaultShakeDuration,Damage);
}

void UDamagerComponent::InitializeDamagerComp(float InEffectRange, int InDamage)
{
	UEffectorComponent::InitializeEffectorComponent(InEffectRange);
	Damage = InDamage;
}

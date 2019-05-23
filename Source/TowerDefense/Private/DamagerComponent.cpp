// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagerComponent.h"
#include "TDCharacter.h"

UDamagerComponent::UDamagerComponent():Damage(0)
{
}

void UDamagerComponent::Effect(ATDCharacter * Target)
{
	Target->TDUnitTakeDamage(8.0f,0.2f,Damage);
}

void UDamagerComponent::InitializeDamagerComp(float iEffectRange,int iDamage)
{
	UEffectorComponent::InitializeEffectorComponent(iEffectRange);
	//EffectRange = iEffectRange;
	Damage=iDamage;
}

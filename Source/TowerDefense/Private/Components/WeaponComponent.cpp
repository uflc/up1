// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "TDCharacter.h"
#include "TDWeaponCommonData.h"


void UWeaponComponent::SetCommonData(UTDWeaponCommonData* InData) 
{ 
	WeaponData = InData; 

	if (!WeaponData) return;

	Cooldown = WeaponData->DefaultCooldown;
	Range	 = WeaponData->DefaultRange;
}

void UWeaponComponent::SetTarget(ATDCharacter* const NewTarget)
{
	Target = NewTarget;
}

bool UWeaponComponent::IsTargetLocked()
{
	return !(Target == nullptr || Target->IsLethal());
}


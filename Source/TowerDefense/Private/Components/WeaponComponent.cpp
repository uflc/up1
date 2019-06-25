// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "TDCharacter.h"
#include "TDWeaponCommonData.h"
#include "Sound\SoundCue.h"

void UWeaponComponent::SetCommonData(UTDWeaponCommonData* InData) 
{ 
	if (!InData || WeaponData == InData) return;

	WeaponData = InData; 

	Cooldown   = WeaponData->GetDefaultCooldown();
	Range	   = WeaponData->GetDefaultRange();
}

void UWeaponComponent::SetTarget(ATDCharacter* const NewTarget)
{
	Target = NewTarget;
}

void UWeaponComponent::UseWeapon() 
{
	USoundBase* Sound = WeaponData->GetAttackSound().Get();
	if (Sound != nullptr)
	{
		UGameplayStatics::PlaySound2D((UObject*)GetWorld(), Sound,1,1,0);
	}
}

bool UWeaponComponent::IsTargetLocked()
{
	return !(Target == nullptr || Target->IsLethal());
}

int32 UWeaponComponent::GetDamage() const
{
	return WeaponData ? WeaponData->GetDefaultDamage() : 0;
}


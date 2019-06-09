// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "TDCharacter.h"
#include "TDWeaponCommonData.h"
#include "Sound\SoundCue.h"
#include "Kismet/GameplayStatics.h"

void UWeaponComponent::SetCommonData(UTDWeaponCommonData* InData) 
{ 
	if (!InData || WeaponData == InData) return;

	WeaponData = InData; 

	Cooldown   = WeaponData->DefaultCooldown;
	Range	   = WeaponData->DefaultRange;
}

void UWeaponComponent::SetTarget(ATDCharacter* const NewTarget)
{
	Target = NewTarget;
}

void UWeaponComponent::UseWeapon() 
{
	USoundBase* Sound 	= WeaponData->FireSoundEffect.Get();
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
	return WeaponData ? WeaponData->DefaultDamage : 0;
}


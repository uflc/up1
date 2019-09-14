// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "TDCharacter.h"
#include "TDWeaponCommonData.h"
#include "Sound\SoundCue.h"

void UWeaponComponent::CooldownEnd()
{
	bInCooldown = false;
}

void UWeaponComponent::SetCommonData(UTDWeaponCommonData* InData)
{ 
	if (!InData || WeaponData == InData) return;

	WeaponData = InData; 

	Cooldown   = WeaponData->GetDefaultCooldown();
	Range	   = WeaponData->GetDefaultRange();

	bInCooldown = false;
}

void UWeaponComponent::SetTarget(ATDCharacter* const NewTarget)
{
	Target = NewTarget;
}

void UWeaponComponent::UseWeapon() 
{
	const static float ProcDelay = 0.2f;

	TD_LOG(Warning, TEXT("%s : UseWeapon"), *GetName());

	USoundBase* Sound = WeaponData->GetAttackSound().Get();
	if (Sound != nullptr)
	{
		UGameplayStatics::PlaySound2D((UObject*)GetWorld(), Sound,1,1,0);
	}

	if (Cooldown <= ProcDelay)
	{
		return;
	}

	bInCooldown = true;

	GetWorld()->GetTimerManager().SetTimer(CooldownHandle,this,&UWeaponComponent::CooldownEnd,Cooldown-ProcDelay,false);
}

bool UWeaponComponent::IsTargetLocked()
{
	return !(Target == nullptr || Target->IsLethal());
}

int32 UWeaponComponent::GetDamage() const
{
	return WeaponData ? WeaponData->GetDefaultDamage() : 0;
}


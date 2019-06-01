// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectWeaponComponent.h"
#include "TDWeaponCommonData.h"
#include "SimpleFlipbookEffect.h"
#include "EffectorComponent.h"
#include "TDCharacter.h"


UDirectWeaponComponent::UDirectWeaponComponent()
{
	Effector = CreateDefaultSubobject<UEffectorComponent>(TEXT("Effector0"));
}

void UDirectWeaponComponent::SetCommonData(UTDWeaponCommonData* InData)
{
	Super::SetCommonData(InData);

	Effector->Initialize(WeaponData->DefaultSplashRange, WeaponData->DefaultDamage);
}

void UDirectWeaponComponent::UseWeapon()
{	
	if (!IsTargetLocked()) return;
	
	if (EffectFlipbook)
	{
		(GetWorld()->SpawnActor<ASimpleFlipbookEffect>(Target->GetActorLocation(), FRotator::ZeroRotator))->SetupEffect(EffectFlipbook);
	}

	Effector->InflictAoE(Target);
}

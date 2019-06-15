// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectWeaponComponent.h"
#include "TDWeaponCommonData.h"
#include "SimpleFlipbookEffect.h"
#include "EffectorComponent.h"
#include "TDCharacter.h"
#include "PaperFlipbook.h"


UDirectWeaponComponent::UDirectWeaponComponent()
{
	Effector = CreateDefaultSubobject<UEffectorComponent>(TEXT("Effector0"));
}

void UDirectWeaponComponent::SetCommonData(UTDWeaponCommonData* InData)
{
	if (!InData || WeaponData == InData) return;

	Super::SetCommonData(InData);

	Effector->Initialize(WeaponData->GetDefaultSplashRange(), WeaponData->GetDefaultDamage(), WeaponData->GetDebuffArray());
}

void UDirectWeaponComponent::UseWeapon()
{	
	//if (!bIsActive) return;
	if (!IsTargetLocked()) return;
	
	Super::UseWeapon();

	Effector->InflictAoE(Target);

	//
	//임시 공격 효과 스폰
	UPaperFlipbook* EffectFlipbook = WeaponData->GetHitFlipbook().Get();
	if (EffectFlipbook)
	{
		ASimpleFlipbookEffect* AttackEffect = GetWorld()->SpawnActor<ASimpleFlipbookEffect>(Target->GetActorLocation(), FRotator::ZeroRotator);
		
		if (AttackEffect)
		{
			AttackEffect->SetupEffect(EffectFlipbook);
		}
	}
}

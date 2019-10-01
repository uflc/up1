// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectWeaponComponent.h"
#include "TDWeaponCommonData.h"
#include "SimpleFlipbookEffect.h"
#include "EffectorComponent.h"
#include "TDCharacter.h"
#include "PaperFlipbook.h"
#include "TDPaperFlipbookComponent.h"

UDirectWeaponComponent::UDirectWeaponComponent()
{
	Effector = CreateDefaultSubobject<UEffectorComponent>(TEXT("Effector0"));
}

void UDirectWeaponComponent::SetCommonData(UTDWeaponCommonData* InData)
{
	if (!InData || WeaponData == InData) return;

	Super::SetCommonData(InData);

	EffectRelativeSpawnPoint=InData->GetEffectVec();
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
		FRotator tempRotator= FRotator::ZeroRotator;
		ATDCharacter* tempOwner = Cast<ATDCharacter>(GetOwner());
		if(tempOwner)
		{ 
			tempRotator=tempOwner->GetAnimation()->GetComponentRotation();
		}
		FVector EffectSpawnVec = Target->GetActorLocation() + EffectRelativeSpawnPoint;
		ASimpleFlipbookEffect* AttackEffect = GetWorld()->SpawnActor<ASimpleFlipbookEffect>(EffectSpawnVec, tempRotator);
		if (AttackEffect)
		{
			if(tempOwner)AttackEffect->SetupEffect(EffectFlipbook,true);
			else AttackEffect->SetupEffect(EffectFlipbook);
		}
	}
}

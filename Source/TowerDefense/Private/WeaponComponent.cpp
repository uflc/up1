// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "TDCharacter.h"
#include "AIController.h"
#include "DebufferComponent.h"
#include "DamagerComponent.h"
#include "TDWeaponCommonData.h"
#include "BehaviorTree\BlackboardComponent.h"


// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent():vTarget(nullptr), SplashRange(0),Cooldown(0),Range(0),Damage(0)
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UWeaponComponent::TargetValidCheck()
{
	if (!vTarget) vTarget = (ATDCharacter*)((AAIController*)((ATDUnit*)GetOwner())->GetController())->GetBlackboardComponent()->GetValueAsObject(FName(TEXT("AggroTarget")));

	if (vTarget->IsValidLowLevelFast() && GetOwner()->IsValidLowLevelFast()) return true;

	return false;
}

void UWeaponComponent::InitializeWeaponComp()
{
	SplashRange=WeaponCommon->DefaultSplashRange;

	Cooldown= WeaponCommon->DefaultCooldown;

	Range= WeaponCommon->DefaultRange;

	// need?
	Damage= WeaponCommon->DefaultDamage;

	if (Damage > 0)	{
		UDamagerComponent* DmgComp= AddSubComponent<UDamagerComponent>();
		if (DmgComp != nullptr) {
			DmgComp->InitializeDamagerComp(SplashRange, Damage);
		}
	}
	
	if( WeaponCommon->DebuffSetArray.Num()!=0) {
	//UDebufferComponent* DebuffComp = AddSubComponent<UDebufferComponent>();
	//		if (DebuffComp != nullptr) {
	//			DebuffComp->InitializeDebufferComp(WeaponCommon->EffectRange, WeaponCommon->DebuffArr, WeaponCommon->DebuffChance);
	//		}
	}
}

inline void UWeaponComponent::SetCommonData(UTDWeaponCommonData* iData) { WeaponCommon = iData; InitializeWeaponComp(); }

void UWeaponComponent::UseWeapon()
{
}

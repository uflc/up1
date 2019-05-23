// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

#include "TDCharacter.h"
#include "AIController.h"

#include "DebufferComponent.h"
#include "DamagerComponent.h"

#include "AIModule\Classes\BehaviorTree\BlackboardComponent.h"


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
	// TODO :: Initialize with common data

	//if (UTDWeaponCommonData.Damage > 0)	{
	//	UDamagerComponent* DmgComp= AddSubComponent<UDamagerComponent>();
	//	if (DmgComp != nullptr) {
	//		DmgComp->InitializeDamagerComp(UTDWeaponCommonData->EffectRange, UTDWeaponCommonData->Damage);
	//	}
	//}
	
	//if( UTDWeaponCommonData.DebuffInfo ) {
	//UDebufferComponent* DebuffComp = AddSubComponent<UDebufferComponent>();
	//if (DebuffComp != nullptr) {
	//		DebuffComp->InitializeDebufferComp(UTDWeaponCommonData->EffectRange, UTDWeaponCommonData->DebuffArr,UTDWeaponCommonData->DebuffChance);
	//	}
	//
	//}
}

void UWeaponComponent::UseWeapon()
{
}

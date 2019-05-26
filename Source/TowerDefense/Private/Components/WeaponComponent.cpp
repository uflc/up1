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
	if (vTarget == nullptr)	{goto EndofCheck;}

	else if(!vTarget->IsTargetable()) 	{goto EndofCheck;}

EndofCheck:

	vTarget=(ATDCharacter*)((AAIController*)((ATDUnit*)GetOwner())->GetController())->GetBlackboardComponent()->GetValueAsObject(FName(TEXT("AggroTarget")));

	if (vTarget->IsValidLowLevelFast() && GetOwner()->IsValidLowLevelFast()) return true;

	return false;
}

void UWeaponComponent::InitializeWeaponComp()
{
	SplashRange	= WeaponData->DefaultSplashRange;
	Cooldown	= WeaponData->DefaultCooldown;
	Range		= WeaponData->DefaultRange;
	Damage		= WeaponData->DefaultDamage;

	if (Damage > 0)	
	{
		UDamagerComponent* DmgComp= AddSubComponent<UDamagerComponent>();
		if (DmgComp != nullptr) 
		{
			DmgComp->InitializeDamagerComp(SplashRange, Damage);
		}
	}
	
	if( WeaponData->DebuffSetArray.Num()!=0) 
	{
	//UDebufferComponent* DebuffComp = AddSubComponent<UDebufferComponent>();
	//		if (DebuffComp != nullptr) {
	//			DebuffComp->InitializeDebufferComp(WeaponCommon->EffectRange, WeaponCommon->DebuffArr, WeaponCommon->DebuffChance);
	//		}
	}
}

void UWeaponComponent::SetCommonData(UTDWeaponCommonData* iData) 
{ 
	WeaponData = iData; 
	InitializeWeaponComp(); 
}

void UWeaponComponent::UseWeapon()
{
}

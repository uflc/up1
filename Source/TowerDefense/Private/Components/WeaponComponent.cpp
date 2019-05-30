// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "TDCharacter.h"
#include "AIController.h"
//#include "DebufferComponent.h"
#include "DamagerComponent.h"
#include "TDWeaponCommonData.h"
#include "BehaviorTree\BlackboardComponent.h"


// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UWeaponComponent::TargetValidCheck()
{
	if (Target == nullptr || !Target->IsTargetable())
	{
		//TODO Event freom BB? //todo 

		const ATDUnit* Owner = (ATDUnit*)GetOwner();
		if (!Owner) return false;

		const AAIController* AICon = (AAIController*)Owner->GetController();
		if (!AICon) return false;

		ATDCharacter* BBTarget = (ATDCharacter*)AICon->GetBlackboardComponent()->GetValueAsObject(FName(TEXT("AggroTarget")));
		Target = BBTarget;
	}

	return Target ? true : false;
}

void UWeaponComponent::InitializeWeaponComp()
{
	SplashRange	= WeaponData->DefaultSplashRange;
	Cooldown	= WeaponData->DefaultCooldown;
	Range		= WeaponData->DefaultRange;
	Damage		= WeaponData->DefaultDamage;

	if (Damage > 0)	
	{
		UDamagerComponent* DmgComp = AddSubComponent<UDamagerComponent>();
		if (DmgComp) 
		{
			DmgComp->InitializeDamagerComp(SplashRange, Damage);
		}
	}
	
	if (WeaponData->DebuffSetArray.Num() != 0) 
	{
	//UDebufferComponent* DebuffComp = AddSubComponent<UDebufferComponent>();
	//if (DebuffComp) 
	//{
	//	DebuffComp->InitializeDebufferComp(WeaponCommon->EffectRange, WeaponCommon->DebuffArr, WeaponCommon->DebuffChance);
	//}
	}
}

void UWeaponComponent::SetCommonData(UTDWeaponCommonData* InData) 
{ 
	WeaponData = InData; 
	InitializeWeaponComp(); 
}

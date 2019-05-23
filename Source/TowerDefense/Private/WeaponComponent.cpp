// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "DebufferComponent.h"
//#include "TDUnit.h"


// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

inline void UWeaponComponent::InitializeAttackComp(const float inSplashRange)
{
	if(AffectRange<0) return;

	AffectRange = inSplashRange;
}

//bool UWeaponComponent::TargetValidCheck()
//{
//	if (!vTarget) vTarget = (ATDCharacter*)((AAIController*)((ATDUnit*)GetOwner())->GetController())->GetBlackboardComponent()->GetValueAsObject(FName(TEXT("AggroTarget")));
//
//	//if(!vTarget) return;
//
//	//ATDCharacter* Target=(ATDCharacter*)((AAIController*)((ATDUnit*)GetOwner())->GetController())->GetBlackboardComponent()->GetValueAsObject(FName(TEXT("AggroTarget")));
//
//	if (vTarget->IsValidLowLevelFast() && GetOwner()->IsValidLowLevelFast()) {}
//}

void UWeaponComponent::Work()
{
}

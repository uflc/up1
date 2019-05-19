// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttackComponent.h"
#include "TDCharacter.h"
void UMeleeAttackComponent::ExecAttack(class UObject* Target)
{
	//++ Create Effect
	
	if(Target->IsValidLowLevelFast() && GetOwner()->IsValidLowLevelFast()){
	((ATDCharacter*)Target)->TDUnitTakeDamage(10.0f,0.2f,((ATDUnit*)GetOwner())->AttackDamage);
	}
	
	//++ Splash Damage Process
}
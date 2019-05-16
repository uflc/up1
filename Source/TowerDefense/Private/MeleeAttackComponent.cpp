// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttackComponent.h"
#include "TDUnit.h"
void UMeleeAttackComponent::ExecAttack(class UObject* Target)
{
	((ATDUnit*)Target)->ApplyDamage(10.0f,0.2f,((ATDUnit*)GetOwner())->UnitAttackDamage);
}
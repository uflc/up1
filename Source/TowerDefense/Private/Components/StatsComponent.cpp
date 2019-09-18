// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"
#include "TDTypes.h"
#include "TDCharacter.h"
#include "TDCharData.h"

void UStatsComponent::TakeDamage(const FDamage & InDamage)
{
	HP -= InDamage.Damage;

	if (HP < 0) 
	{
		Cast<ATDCharacter>(GetOwner())->OnTDUnitDeath.Broadcast();
	}
}

void UStatsComponent::SetCommonData(UTDCharData * InData)
{
	HP=InData->GetHealth();
}

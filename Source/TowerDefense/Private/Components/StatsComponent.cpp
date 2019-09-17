// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"
#include "TDTypes.h"
#include "TDCharData.h"

void UStatsComponent::TakeDamage(const FDamage & InDamage)
{
	HP -= InDamage.Damage;

	OnHealthChanged.Broadcast();

	//if (HP < 0) 
	//{
	//		OnDied.Broadcast()
	//}
}

void UStatsComponent::SetCommonData(UTDCharData * InData)
{
	HP=InData->GetHealth();
}

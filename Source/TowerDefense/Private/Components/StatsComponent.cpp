// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"
#include "TDTypes.h"
#include "TDCharData.h"

void UStatsComponent::TakeDamage(const FDamage & InDamage)
{
	SetHP(HP - InDamage.Damage);

	//if (HP < 0) 
	//{
	//		OnDied.Broadcast()
	//}
}

void UStatsComponent::SetHP(int32 InHP)
{
	if (InHP == HP) return;

	HP = InHP;
	OnHealthChanged.Broadcast();

}

void UStatsComponent::SetCommonData(UTDCharData * InData)
{
	HP=InData->GetHealth();
}

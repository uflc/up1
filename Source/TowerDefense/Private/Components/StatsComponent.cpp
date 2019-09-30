// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"
#include "TDTypes.h"
#include "TDCharacter.h"
#include "TDCharData.h"

void UStatsComponent::TakeDamage(const FDamage & InDamage)
{
	//TD_LOG(Warning, TEXT("Stat : TakeDamage"));
	SetHP(HP - InDamage.Damage);

	if (HP >= MaxHP)
	{
		SetHP(MaxHP);
	}
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
	MaxHP= InData->GetHealth();
}

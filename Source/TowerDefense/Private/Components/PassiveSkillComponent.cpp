// Fill out your copyright notice in the Description page of Project Settings.


#include "PassiveSkillComponent.h"
#include "TDCharacter.h"
#include "PassiveCommonData.h"
#include "Sound\SoundCue.h"

void UPassiveSkillComponent::DelayEnd()
{
}

void UPassiveSkillComponent::SetCommonData(UPassiveCommonData* InData)
{
	if (!InData || SkillData == InData) return;

	SkillData = InData;

	Cooldown = SkillData->GetDefaultCooldown();
	AggroRange = SkillData->GetDefaultAggroRange();
	EffectRange = SkillData->GetDefaultEffectRange();

	//bInCooldown = false;
}

void UPassiveSkillComponent::SetTarget(ATDCharacter * const NewTarget)
{
	Target = NewTarget;
}

void UPassiveSkillComponent::Initialize_Implementation()
{
}


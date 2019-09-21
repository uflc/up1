// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TDComponent.h"
#include "PassiveSkillComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract, EditInlineNew, meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UPassiveSkillComponent : public UTDComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ATDCharacter* Target;

	UPROPERTY(BlueprintReadOnly)
	class UPassiveCommonData* SkillData;

	UPROPERTY(BlueprintReadOnly)
	float Cooldown;

	UPROPERTY(BlueprintReadOnly)
	float AggroRange;

	UPROPERTY(BlueprintReadOnly)
	float EffectRange;

	//UPROPERTY(BlueprintReadOnly)
	//bool bInCooldown;

	FTimerHandle DelayHandle;

	void DelayEnd();

public:
	virtual void SetCommonData(UPassiveCommonData* InData);

	UFUNCTION(BlueprintSetter)
	void SetTarget(ATDCharacter* const NewTarget);

	UFUNCTION(BlueprintCallable)
	virtual void ActivateSkill();

	FORCEINLINE float GetAggroRange() const { return AggroRange; }
	FORCEINLINE float GetEffectRange() const { return EffectRange; }
};

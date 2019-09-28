// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components\SceneComponent.h"
#include "PassiveSkillComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract, EditInlineNew, meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UPassiveSkillComponent : public USceneComponent
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
	UFUNCTION(BlueprintCallable)
	virtual void SetCommonData(UPassiveCommonData* InData);

	UFUNCTION(BlueprintSetter)
	void SetTarget(ATDCharacter* const NewTarget);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Initialize();

	virtual void Initialize_Implementation();
	
	FORCEINLINE float GetAggroRange() const { return AggroRange; }
	FORCEINLINE float GetEffectRange() const { return EffectRange; }
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TDComponent.h"
#include "WeaponComponent.generated.h"

//todo accessor
UCLASS(Blueprintable, Abstract, EditInlineNew, meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UWeaponComponent : public UTDComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ATDCharacter* Target;

	UPROPERTY(BlueprintReadOnly)
	class UTDWeaponCommonData* WeaponData;

	UPROPERTY(BlueprintReadOnly)
	float Cooldown;

	UPROPERTY(BlueprintReadOnly)
	float Range;

	UPROPERTY(BlueprintReadOnly)
	bool bInCooldown;

	FTimerHandle CooldownHandle;

	void CooldownEnd();

public:		
	UFUNCTION(BlueprintCallable)
	virtual void SetCommonData(UTDWeaponCommonData* InData);

	UFUNCTION(BlueprintSetter)
	void SetTarget(ATDCharacter* const NewTarget);

	UFUNCTION(BlueprintCallable)
	virtual void UseWeapon();

	virtual bool IsTargetLocked();

	
	FORCEINLINE float GetRange() const { return Range; }
	FORCEINLINE float GetCooldown() const { return Cooldown; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsInCooldown() const { return bInCooldown; }

	UFUNCTION(BlueprintPure)
	int32 GetDamage() const;
};

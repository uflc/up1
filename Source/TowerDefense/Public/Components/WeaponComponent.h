// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDComponent.h"
#include "WeaponComponent.generated.h"


UCLASS(Blueprintable, Abstract, ClassGroup=(Custom))
class TOWERDEFENSE_API UWeaponComponent : public UTDComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ATDCharacter* Target;

	UPROPERTY(BlueprintReadOnly)
	class UTDWeaponCommonData* WeaponData;

	UPROPERTY(BlueprintReadOnly)
	float SplashRange;

	UPROPERTY(BlueprintReadOnly)
	float Cooldown;

	UPROPERTY(BlueprintReadOnly)
	float Range;

	UPROPERTY(BlueprintReadOnly)
	int Damage;

	UPROPERTY(BlueprintReadOnly)
	float UpgradedLevel;

public:	
	bool TargetValidCheck();

	UFUNCTION(BlueprintCallable)
	void InitializeWeaponComp();

	//UFUNCTION(BlueprintCallable)
	void SetCommonData(UTDWeaponCommonData* InData);

	UFUNCTION(BlueprintCallable)
	virtual void UseWeapon();
};

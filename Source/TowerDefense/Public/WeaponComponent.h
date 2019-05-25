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
	class ATDCharacter* vTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTDWeaponCommonData* WeaponCommon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SplashRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UpgradedLevel;

public:	
	bool TargetValidCheck();

	UFUNCTION(BlueprintCallable)
	void InitializeWeaponComp();

	//UFUNCTION(BlueprintCallable)
	void SetCommonData(UTDWeaponCommonData* iData);

	UFUNCTION(BlueprintCallable)
	virtual void UseWeapon();
};

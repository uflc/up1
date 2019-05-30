// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDComponent.h"
#include "WeaponComponent.generated.h"

//todo accessor
UCLASS(Blueprintable, Abstract, ClassGroup=(Custom))
class TOWERDEFENSE_API UWeaponComponent : public UTDComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ATDCharacter* Target	 = nullptr;

	UPROPERTY(BlueprintReadOnly)
	class UTDWeaponCommonData* WeaponData = nullptr;

	UPROPERTY(BlueprintReadOnly)
	float SplashRange = 0;

	UPROPERTY(BlueprintReadOnly)
	float Cooldown = 0;

	UPROPERTY(BlueprintReadOnly)
	float Range = 0;

	UPROPERTY(BlueprintReadOnly)
	int	Damage = 0;

	UPROPERTY(BlueprintReadOnly)
	int	UpgradedLevel = 0;

public:	
	bool TargetValidCheck();

	UFUNCTION(BlueprintCallable)
	void InitializeWeaponComp();

	//UFUNCTION(BlueprintCallable)
	void SetCommonData(UTDWeaponCommonData* InData);

	UFUNCTION(BlueprintCallable)
	virtual void UseWeapon() {}
};

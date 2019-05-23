// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectorComponent.h"
#include "WeaponComponent.generated.h"


UCLASS(Blueprintable, Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UWeaponComponent : public UEffectorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Damage;

public:	
	UFUNCTION(BlueprintCallable)
	virtual void InitializeAttackComp(const float inSplashRange);

	//How about this?
	//UFUNCTION(BlueprintCallable)
	//virtual void InitializeAttackComp(const UTDWeaponCommonData&);

	UFUNCTION(BlueprintCallable)
	virtual void ExecAttack(class ATDCharacter* Target){}

	virtual void Work() override;

	virtual void Affect(ATDCharacter* Target){}
};

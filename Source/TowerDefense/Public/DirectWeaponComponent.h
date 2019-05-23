// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "DirectWeaponComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UDirectWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()

	UDirectWeaponComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbook* EffectFlipbook;

public:

	UFUNCTION(BlueprintCallable)
	void InitializeMeleeComp(const float inSplashRange, UPaperFlipbook* inEffectFlipbook);

	virtual void ExecAttack(class ATDCharacter* Target) override;

	virtual void Work() override;

	virtual void Affect(ATDCharacter* Target) override;
};

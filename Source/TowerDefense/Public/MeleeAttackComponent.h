// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "MeleeAttackComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UMeleeAttackComponent : public UAttackComponent
{
	GENERATED_BODY()

	UMeleeAttackComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbook* EffectFlipbook;

public:
	void Initialize() override;

	void Initialize(const float inSplashRange, UPaperFlipbook* inEffectFlipbook);

	virtual void ExecAttack(class ATDCharacter* Target) override;
};

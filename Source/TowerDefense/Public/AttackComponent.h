// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDComponent.h"
#include "AttackComponent.generated.h"


UCLASS(Blueprintable, Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UAttackComponent : public UTDComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

protected:

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SplashRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class UDebufferComponent>> Debuffers;

public:	
	UFUNCTION(BlueprintCallable)
		void Initialize(const float inSplashRange);

	virtual void Initialize();

	UFUNCTION(BlueprintCallable)
	virtual void ExecAttack(class UObject* Target){}

	void SetupDebuffers();
};

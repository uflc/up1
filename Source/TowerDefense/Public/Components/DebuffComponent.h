// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TDComponent.h"
#include "TDTypes.h"
#include "DebuffComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UDebuffComponent : public UTDComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FDebuffSet DebuffInfo;

	UFUNCTION(BlueprintCallable)
	void Initialize(const FDebuffSet& InDebuffInfo);

	/*UFUNCTION(BlueprintCallable)
	void ActivateDebuff();

	UFUNCTION(BlueprintCallable)
	void DeactivateDebuff();*/
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TDComponent.h"
#include "StatsComponent.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UStatsComponent : public UTDComponent
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthChangeSignature);

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TDChar")
	int32 HP;

	UPROPERTY(BlueprintAssignable)
	FHealthChangeSignature OnHealthChanged;

public:
	UFUNCTION()
	void TakeDamage(const FDamage& InDamage);

	UFUNCTION(BlueprintCallable)
	void SetHP(int32 InHP);

	FORCEINLINE int32 GetHP() const{ return HP; }

	virtual void SetCommonData(class UTDCharData* InData);
};

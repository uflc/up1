// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TDComponent.h"
#include "TDTypes.h"
#include "UnitDebuffComponent.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UUnitDebuffComponent : public UTDComponent
{
	GENERATED_BODY()
	
public:
	UUnitDebuffComponent();

protected:	
	//UPROPERTY() Cannot use UPROPERTY
	TMultiMap<EDebuffType,FDebuff> DebuffMap;

public:
	UFUNCTION()
	void RegDebuff(const FDebuff& Debuff);

	UFUNCTION()
	void UnregDebuff(const FDebuff & Debuff);

	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void UpdateStat(const EDebuffType& InDebuffType); // Broadcast?

	void test(){}
};

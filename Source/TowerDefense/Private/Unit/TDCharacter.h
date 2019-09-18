// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TDUnit.h"
#include "TDCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDCharacter : public ATDUnit
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthChangeSignature);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTakeDamageSignature, const FDamage& , InDamage);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTDUnitDeathSignature);
	
public:
	ATDCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStatsComponent* Stats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPawnMovementComponent* Movement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUnitDebuffComponent* DebuffControll;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent* HealthBar;

	UPROPERTY(BlueprintReadOnly, Category = "TDChar")
	float DrawingAggroRange;

	UPROPERTY(BlueprintReadOnly, Category = "TDChar")
	float AggroDrawnRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TDChar")
	int32 Health;
	
	/*UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "TDChar")
	TSet<EDebuffType> Disables;*/

public:
	UPROPERTY(BlueprintAssignable)
	FHealthChangeSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FTakeDamageSignature OnTakeDamage;

	UPROPERTY(BlueprintAssignable)
	FTDUnitDeathSignature OnTDUnitDeath;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//Tick마다 콜. 좌우 방향을 체크해서 스프라이트 로테이트. 
	//TODO any Event?
	virtual void UpdateDirection();

	//TODO AActor::TakeDamge override?
	UFUNCTION(BlueprintCallable)
	void TDUnitTakeDamage(const FDamage & InDamage);

	//virtual void TakeDamge();

	//UFUNCTION(BlueprintCallable)
	//void TDUnitTakeDebuff(FDebuff& InDebuff);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Die();
	virtual void Die_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnDeath();
	virtual void OnDeath_Implementation();

	virtual float GetAggroRange() const override;

	//EUnitState Dying or Dead
	UFUNCTION(BlueprintPure)
	bool IsLethal() const;
};

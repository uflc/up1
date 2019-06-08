// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDUnit.h"
#include "TDTypes.h"
#include "TDCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDCharacter : public ATDUnit
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthChangeSignature);
	
public:
	ATDCharacter();

protected:
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

	UPROPERTY(BlueprintAssignable)
	FHealthChangeSignature OnHealthChanged;

	/*UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "TDChar")
	TSet<EDebuffType> Disables;*/

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	virtual bool UpdateAnimation() override;

	//Tick마다 콜. 좌우 방향을 체크해서 스프라이트 로테이트. 
	//TODO any Event?
	virtual void UpdateDirection();

	//EUnitState Dying or Dead
	UFUNCTION(BlueprintPure)
	bool IsLethal();

	//TODO AActor::TakeDamge override?
	UFUNCTION(BlueprintCallable)
	void TDUnitTakeDamage(float ShakePower, float ShakeDuration, int32 Damage);

	UFUNCTION(BlueprintCallable)
	void TDUnitTakeDebuff(FDebuff & InDebuff);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Die();
	virtual void Die_Implementation();

	void OnDeath();

	virtual float GetAggroRange() const override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDUnit.h"
#include "TDCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDCharacter : public ATDUnit
{
	GENERATED_BODY()
	
public:
	ATDCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPawnMovementComponent* Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float DrawingAggroRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	int32 Health;

public:
	virtual void Tick(float DeltaTime) override;

	virtual bool UpdateAnimation() override;

	//Tick���� ��. �¿� ������ üũ�ؼ� ��������Ʈ ������Ʈ. 
	//@TODO any Event?
	virtual void UpdateDirection();

	//@TODO AActor::TakeDamge override?
	UFUNCTION(BlueprintCallable)
	void TDUnitTakeDamage(float ShakePower, float ShakeDuration, int32 Damage);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Die();
	virtual void Die_Implementation();

	void OnDeath();
};

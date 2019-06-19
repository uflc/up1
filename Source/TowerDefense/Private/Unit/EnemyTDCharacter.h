// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/TDCharacter.h"
#include "EnemyTDCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AEnemyTDCharacter : public ATDCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyTDCharacter();
	
protected:
	// ���̺� Destination�� ���� ���� �� �÷��̾�� �ִ� ���ط�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 LifeDamage;

	// �÷��̾ óġ���� �� ��� �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Bounty;

public:
	virtual void PostInitializeComponents() override;

	// �ӽ÷� �÷��̾�� óġ ������� �ֵ��� ��.
	virtual void Die_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual void Finish();
};

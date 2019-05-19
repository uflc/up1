// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "TDTypes.h"
#include "TDUnit.generated.h"


/**
 * 
 ������Ʈ, ��, ���� ��׷� ���.
 ��ü���� �ൿ ������ BT BP�� ��.
 */
UCLASS(BluePrintable)
class TOWERDEFENSE_API ATDUnit : public APaperCharacter
{
	GENERATED_BODY()

	//static FName ShadowComponentName;
	//static FName AttackComponentName;

public:
	ATDUnit();
	
protected:
	UPROPERTY(Category = "TDUnit|Effect", VisibleAnywhere, BlueprintReadWrite)
	class UPaperSpriteComponent* Shadow;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadWrite)
	class UAttackComponent* AttackComp;

	virtual void BeginPlay() override;

	//@Note AnimState for now
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|State")
	EUnitState UnitState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|State")
	EDirection Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	EUnitTeam Team;

	//@TODO �ʿ� or BT only?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ATDCharacter* AggroTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float AttackDelay;	
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float AggroDrawnRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	TSoftObjectPtr<class UTDUnitCommonData> Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	TSubclassOf<UAttackComponent> AttackCompClass;

public:
	UFUNCTION()
	virtual class UPaperFlipbook* GetDesiredAnimation();

	//@Note ���� ���¿� �´� �ִϸ��̼����� ������Ʈ
	UFUNCTION(BlueprintCallable, Category = "TDUnit|Animation")
	virtual bool UpdateAnimation();

	//@Note this will call UpdateAnimation
	UFUNCTION(BlueprintCallable, Category = "TDUnit|Animation")
	void ChangeState(EUnitState InState);

	UFUNCTION(BlueprintCallable, Category = "TDUnit|State")
	virtual void UpdateDirection();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void InitializeTDComponents();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	int32 AttackDamage;
};

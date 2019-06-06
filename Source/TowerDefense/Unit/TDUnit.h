// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFrameWork/Pawn.h"
#include "TDTypes.h"
#include "TDUnit.generated.h"


/**
 * 
 ������Ʈ, ��, ���� ��׷� ���.
 ��ü���� �ൿ ������ BT BP�� ��.
 @TODO Access 
 */
UCLASS(BluePrintable)
class TOWERDEFENSE_API ATDUnit : public APawn
{
	GENERATED_BODY()

	//static FName ShadowComponentName;
	//static FName AttackComponentName;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponChangeSignature);

public:
	ATDUnit();

protected:
	UPROPERTY(Category = Unit, VisibleAnywhere, BlueprintReadOnly)
	class UPaperFlipbookComponent* Animation;

	UPROPERTY(Category = Unit, VisibleAnywhere, BlueprintReadWrite)
	class UPaperSpriteComponent* Shadow;

	UPROPERTY(Category = Unit, VisibleAnywhere, BlueprintReadWrite)
	class UWeaponComponent* AttackComp;

	//@Note AnimState for now
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|State")
	EUnitState UnitState;

	//@TODO Tower Only?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|State")
	EDirection Direction;

	//@TODO �ʿ� or BT only?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ATDCharacter* AggroTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	class UTDUnitCommonData* UnitData;

	virtual void BeginPlay() override;


public:
	virtual void PostInitializeComponents() override;

	FWeaponChangeSignature OnWeaponChanged;

	//AttackComp weapon is Unique
	virtual void CreateUniqueWeapon();

	UFUNCTION()
	virtual class UPaperFlipbook* GetDesiredAnimation();

	//���� ���¿� �´� �ִϸ��̼����� ������Ʈ
	UFUNCTION(BlueprintCallable, Category = "TDUnit|Animation")
	virtual bool UpdateAnimation();

	//this will call UpdateAnimation
	UFUNCTION(BlueprintCallable, Category = "TDUnit|Animation")
	void ChangeState(EUnitState InState);

	UFUNCTION(BlueprintCallable, Category = "TDUnit|Animation")
	virtual void UpdateDirection() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	EUnitTeam Team;

	//By default we use attack range as aggro range. Also, this is called in BTService AggroCheck to see if enemy is in aggro range.
	UFUNCTION(BlueprintPure)
	virtual float GetAggroRange() const;

	////- for global range?
	UFUNCTION(BlueprintPure)
	float GetAttackRange() const;
};

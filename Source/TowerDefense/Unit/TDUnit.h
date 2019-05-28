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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	EUnitTeam Team;

	UFUNCTION(BlueprintCallable, Category = "TDUnit|State")
	bool IsTargetable();
};

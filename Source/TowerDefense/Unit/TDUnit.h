// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFrameWork/Pawn.h"
#include "TDTypes.h"
#include "TDUnit.generated.h"


/**
 * 
 스테이트, 팀, 공격 어그로 등등.
 구체적인 행동 로직은 BT BP로 함.
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

	virtual void BeginPlay() override;

	//@Note AnimState for now
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|State")
	EUnitState UnitState;

	//@TODO Tower Only?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|State")
	EDirection Direction;


	//@TODO 필요 or BT only?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ATDCharacter* AggroTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float AttackDelay;	
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float AggroDrawnRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	class UTDUnitCommonData* Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	TSubclassOf<UWeaponComponent> AttackCompClass;

public:
	UFUNCTION()
	virtual class UPaperFlipbook* GetDesiredAnimation();

	//@Note 현재 상태에 맞는 애니메이션으로 업데이트
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	EUnitTeam Team;

	UFUNCTION(BlueprintCallable, Category = "TDUnit|State")
	bool IsTargetable();
};

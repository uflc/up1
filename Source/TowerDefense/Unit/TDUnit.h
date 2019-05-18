// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperCharacter.h"
#include "TDUnit.generated.h"

class UTDUnitCommonData;
UENUM(BlueprintType)
enum class EUnitTeam : uint8
{
	None	UMETA(DisplayName = "None"),
	Player	UMETA(DisplayName = "Player"),
	Enemy	UMETA(DisplayName = "Enemy"),
};

/**
 * 
 �� ������ ��� ĳ���� ������ ��ӹ��� Ŭ����.
 ������Ʈ, ��, ���� ��׷� ��� �� ������ ���ֵ鿡�� �������� ��� ����.
 ��ü���� �ൿ ������ BT BP�� ��.
 */
UCLASS(BluePrintable)
class TOWERDEFENSE_API ATDUnit : public APaperCharacter
{
	GENERATED_BODY()

public:
	ATDUnit();

protected:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadWrite)
	class UPaperSpriteComponent* Shadow;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadWrite)
	class UAttackComponent* AttackComp;

	virtual void BeginPlay() override;

	//@Note AnimState
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|State")
	EUnitState UnitState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	EUnitTeam Team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float UnitAttackDelay;	
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float AggroDrawnRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	TSoftObjectPtr<UTDUnitCommonData> Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	TSubclassOf<UAttackComponent> AttackCompClass;

public:
	UFUNCTION()
	virtual bool ChangeAnimation();

	//@Note AnimState this will call ChangeAnimation
	UFUNCTION(BlueprintCallable, Category = "TDUnit|State")
	void ChangeState(EUnitState InState);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	int32 UnitAttackDamage;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void InitializeTDComponents();
};

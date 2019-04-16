// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperCharacter.h"
#include "MyPaperCharacter.generated.h"

UENUM(BlueprintType)
enum class EUnitState : uint8
{
	Idle		UMETA(DisplayName="Idle"),
	Attacking	UMETA(DisplayName="Attaking"),
	Running		UMETA(DisplayName="Running"),
	Dying		UMETA(DisplayName="Dying"),
	Dead		UMETA(DisplayName="Dead")
};

UENUM(BlueprintType)
enum class EUnitTeam : uint8
{
	None	UMETA(DisplayName = "None"),
	Player	UMETA(DisplayName = "Player"),
	Enemy	UMETA(DisplayName = "Enemy"),
};


class AMyPaperCharacter;

/*
공통된 데이터를 한 인스턴트에 담으려고 만든 클래스이지만 블루프린트에 적합하지 않아 보이므로 보류.
*/
UCLASS(Blueprintable)
class WORK2_API UMyPaperCharacterCommon : public UObject
{
	GENERATED_BODY()
	
protected:
	friend class AMyPaperCharacter;

	
};

/**
 * 
 */
UCLASS(BluePrintable)
class WORK2_API AMyPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AMyPaperCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
	EUnitState UnitState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
	EUnitTeam Team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TMap<EUnitState, TSoftObjectPtr<UPaperFlipbook>> FlipbookMap;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
	float AttackRange;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
	float AggroDrawnRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
	float DrawingAggroRange;

	//보류
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
	//TSoftObjectPtr<UMyPaperCharacterCommon> Data;



public:
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void UpdateAnimation();
	//virtual void UpdateAnimation_Implementation();
	

};

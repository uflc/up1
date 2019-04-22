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


/**
 * 
 이 게임의 모든 캐릭터 유닛이 상속받을 클래스.
 스테이트, 팀, 공격 어그로 등등 이 게임의 유닛들에게 공통적인 기능 제공.
 구체적인 행동 로직은 BT BP로 함.
 */
UCLASS(BluePrintable)
class WORK2_API AMyPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

	/*UPROPERTY(Config)
	TArray<FStringAssetReference> UnitFlipbooks;*/

public:
	AMyPaperCharacter();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit State")
	EUnitState UnitState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
	EUnitTeam Team;

	//편해서 쓰는데, 퍼포먼스 문제가 생긴다면 따로 단일 인스턴스를 공유하도록 해야 될 것 같지만 큰 영향은 없을 듯.
	UPROPERTY(EditAnywhere,	BlueprintReadWrite, Category = "Animation")
	TMap<EUnitState, TAssetPtr<UPaperFlipbook>> FlipbookMap;


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
	bool UpdateAnimation();
	//virtual void UpdateAnimation_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Unit State")
	void ChangeState(EUnitState InState);

	void BeginPlay();

	void FlipbooksDeffered();
	
};

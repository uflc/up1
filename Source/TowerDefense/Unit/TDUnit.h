// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperCharacter.h"
#include "TDUnit.generated.h"

class ATower;
class UTDUnitCommonData;
//enum class EUnitState : uint8;
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
class TOWERDEFENSE_API ATDUnit : public APaperCharacter
{
	GENERATED_BODY()

public:
	ATDUnit();
protected:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadWrite)
	class UPaperSpriteComponent* Shadow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|State")
	EUnitState UnitState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	EUnitTeam Team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	int32 UnitHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float UnitAttackDelay;	
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	int32 UnitAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float AggroDrawnRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float DrawingAggroRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	TSoftObjectPtr<UTDUnitCommonData> Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDelayChecking;

	FTimerHandle ActionTimerHandle;
public:
	UFUNCTION(BlueprintCallable, Category = "Animation")
	bool UpdateAnimation();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "TDUnit|State")
	void ChangeState(EUnitState InState);

	UFUNCTION(BlueprintCallable, Category = "TDUnit|State")
	void ApplyDamage(float ShakePower, float ShakeDuration, int32 Damage);	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CharacterDestroy();

	UFUNCTION(BlueprintCallable)
	void CharacterDestroy_Implementation();

	UFUNCTION(BlueprintCallable)
	void StartAttack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void execAttack();

	//UFUNCTION(BlueprintCallable)
	void execAttack_Implementation();
};

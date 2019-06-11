// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFrameWork/Pawn.h"
#include "TDTypes.h"
#include "TDUnit.generated.h"


/**
 * 
 * 적을 공격할 수 있는 스프라이트 애니메이팅 폰.
 * TODO Access 
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
	UPROPERTY(Category = TDUnit, VisibleAnywhere, BlueprintReadOnly)
	class UTDUnitCommonData* UnitData;

	//Root. Collision.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* Box;

	//Visual representation.
	UPROPERTY(Category = TDUnit, VisibleAnywhere, BlueprintReadOnly)
	class UPaperFlipbookComponent* Animation;

	UPROPERTY(Category = TDUnit, VisibleAnywhere, BlueprintReadOnly)
	class UPaperSpriteComponent* Shadow;

	//고유한 주 사용 무기(공격 방식).
	UPROPERTY(Category = TDUnit, VisibleAnywhere, BlueprintReadOnly)
	class UWeaponComponent* AttackComp;
	//TODO 다양한 WeaponComponent로 여러 공격 및 스킬 구현.

	//피아 식별. Player는 Enemy에게 어그로가 끌리며 역도 성립. 기본값인 None은 깍두기.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit")
	EUnitTeam Team;

	//행동 상태. 이에 따라 애니메이션이 결정됨.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit")
	EUnitState UnitState;

	//바라보는 방향. 이에 따라 애니메이션이 결정됨. //TODO Tower Only? But 타워 외에도 방향에 따른 애니메이션 추가 될지 모름.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TDUnit")
	EDirection Direction;

	virtual void BeginPlay() override;

public:
	virtual void PostInitializeComponents() override;

	FWeaponChangeSignature OnWeaponChanged;

	//AttackComp weapon is Unique
	virtual void CreateUniqueWeapon();

	//적절한 애니메이션으로 업데이트. 루핑 애니메이션은 재생됨. See UPaperFlipbookComponent::SetFlipbook()
	UFUNCTION(BlueprintCallable, Category = "Animation")
	virtual void UpdateAnimation();

	//행동 상태를 바꾸고 적절한 애니메이션으로 업데이트. See UpdateAnimation()
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void ChangeState(EUnitState InState);

	//현재 상태에 알맞은 애니메이션을 구함.
	UFUNCTION(BlueprintNativeEvent)
	class UPaperFlipbook* GetDesiredAnimation();
	virtual UPaperFlipbook* GetDesiredAnimation_Implementation();

	//this is called in BTService AggroCheck() to see if enemy is in aggro range.
	UFUNCTION(BlueprintPure)
	virtual float GetAggroRange() const;

	////- for global range?
	UFUNCTION(BlueprintPure)
	float GetAttackRange() const;

	UFUNCTION(BlueprintPure)
	int32 GetAttackDamage() const;

	UFUNCTION(BlueprintPure)
	float GetAttackSpeed() const;

	EUnitTeam GetTeam() const { return Team; }
};

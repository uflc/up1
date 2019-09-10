// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "TDTypes.h"
#include "TDUnit.generated.h"


/**
 * 
 * 적을 공격할 수 있는 스프라이트 애니메이팅 폰.
 * TODO Access 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API ATDUnit : public APawn
{
	GENERATED_BODY()

	//static FName ShadowComponentName;
	//static FName AttackComponentName;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponChangeSignature);

public:
	ATDUnit();
	ATDUnit(const FObjectInitializer& ObjectInitializer);

private:
	//test
	UPROPERTY(EditAnywhere)
	bool bIsSpriteDirectional;

	void InitializeDefaults();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UTDUnitCommonData* UnitData;

	//Root. Collision.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* Box;

	//Visual representation.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTDPaperFlipbookComponent* Animation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPaperSpriteComponent* Shadow;

	//고유한 주 사용 무기(공격 방식).
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWeaponComponent* WeaponComp;

	//TODO 다양한 WeaponComponent로 여러 공격 및 스킬 구현.
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly)
	TArray<UWeaponComponent*> SkillCompArr;

	//피아 식별. Player는 Enemy에게 어그로가 끌리며 역도 성립. 기본값인 None은 깍두기.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUnitTeam Team;

	virtual void BeginPlay() override;

	virtual void SetFlipbooks();

	virtual void ApplyData();

	FORCEINLINE bool IsSpriteDirectional() const { return bIsSpriteDirectional; }
	
public:
	//virtual void PostInitProperties() override;
	//virtual void PreRegisterAllComponents() override;
	//virtual void PostInitializeComponents() override;

	FWeaponChangeSignature OnWeaponChanged;

	//AttackComp weapon is Unique
	virtual void CreateUniqueWeapon();

	virtual void CreateSkills();

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

	FORCEINLINE EUnitTeam GetTeam() const { return Team; }

	static FName AnimationComponentName;
	FORCEINLINE UTDPaperFlipbookComponent* GetAnimation() const { return Animation; }
};

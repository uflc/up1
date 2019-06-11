// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFrameWork/Pawn.h"
#include "TDTypes.h"
#include "TDUnit.generated.h"


/**
 * 
 * ���� ������ �� �ִ� ��������Ʈ �ִϸ����� ��.
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

	//������ �� ��� ����(���� ���).
	UPROPERTY(Category = TDUnit, VisibleAnywhere, BlueprintReadOnly)
	class UWeaponComponent* AttackComp;
	//TODO �پ��� WeaponComponent�� ���� ���� �� ��ų ����.

	//�Ǿ� �ĺ�. Player�� Enemy���� ��׷ΰ� ������ ���� ����. �⺻���� None�� ��α�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit")
	EUnitTeam Team;

	//�ൿ ����. �̿� ���� �ִϸ��̼��� ������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit")
	EUnitState UnitState;

	//�ٶ󺸴� ����. �̿� ���� �ִϸ��̼��� ������. //TODO Tower Only? But Ÿ�� �ܿ��� ���⿡ ���� �ִϸ��̼� �߰� ���� ��.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TDUnit")
	EDirection Direction;

	virtual void BeginPlay() override;

public:
	virtual void PostInitializeComponents() override;

	FWeaponChangeSignature OnWeaponChanged;

	//AttackComp weapon is Unique
	virtual void CreateUniqueWeapon();

	//������ �ִϸ��̼����� ������Ʈ. ���� �ִϸ��̼��� �����. See UPaperFlipbookComponent::SetFlipbook()
	UFUNCTION(BlueprintCallable, Category = "Animation")
	virtual void UpdateAnimation();

	//�ൿ ���¸� �ٲٰ� ������ �ִϸ��̼����� ������Ʈ. See UpdateAnimation()
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void ChangeState(EUnitState InState);

	//���� ���¿� �˸��� �ִϸ��̼��� ����.
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

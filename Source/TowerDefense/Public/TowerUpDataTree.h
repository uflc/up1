// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDTypes.h"
#include "TowerUpDataTree.generated.h"


//@Note TArray with FixedAlloc or c++ fixed array reference BP ������
//@ https://docs.unrealengine.com/en-us/Programming/Development/CodingStandard#stongly-typedenums ��..
//@Ÿ�� Ÿ�� ���׷��̵� Ʈ��
//@��� �迭 �ּҴ� Ÿ�԰� ��ġ�ؾ���.
//@TODO make const or FORCEINLINE ??
UCLASS(BlueprintType)
class UTowerUpData : public UDataAsset
{
	GENERATED_BODY()

friend class ATower;
friend class ATDGameModeBase;

private:
	//@Ÿ�� �׼Ǹ޴����� �� ���׷��̵� �̸����� �̹���
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<class UTexture2D> UpPreviews[UPGRADES_NUM];

	//@��Ī �ø��� �迭 �ּҴ� UnitState * Direction as Byte
	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<class UPaperFlipbook>> Animations;

	//@���� Ÿ�Կ��� ������ ���׷��̵� Ÿ��
	UPROPERTY(EditAnywhere)
	UTowerUpData* Upgrades[UPGRADES_NUM];

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 UpAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 UpAttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 UpAttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ABulletBase> BulletType;

public:

	//@return nullptr when UpType is not valid.
	UFUNCTION(BlueprintPure)
	UTowerUpData* GetNextUpgraded(const ETowerType& UpType);

	//@���� Ÿ�Կ��� ������ ���׷��̵� Ʈ��
	UFUNCTION(BlueprintPure)
	UTowerUpData* GetUpgraded(const TArray<ETowerType>& UpTypes);

	//@Note BP��. c++������ TArray�� ī���� �ʿ䰡 ���� ����. see class note
	UFUNCTION(BlueprintPure)
	TArray<TSoftObjectPtr<class UTexture2D>> GetUpPreviews();

	//@return Animation of current level, direction and state
	UFUNCTION(BlueprintCallable)
	UPaperFlipbook* GetMatchingAnim(const EDirection& Direction, const EUnitState& State);
};

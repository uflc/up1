// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDTypes.h"
#include "TowerDataTree.generated.h"

USTRUCT(BlueprintType)
struct FTowerUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UTowerData* Upgrade;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<class UTexture2D> UpPreview;
};


//@Note TArray with FixedAlloc or c++ fixed array reference BP ������
//@ https://docs.unrealengine.com/en-us/Programming/Development/CodingStandard#stongly-typedenums ��..
//@Ÿ�� Ÿ�� ���׷��̵� Ʈ��
//@TODO BlueprintPure or const or FORCEINLINE ??
UCLASS(BlueprintType)
class UTowerData : public UDataAsset
{
	GENERATED_BODY()

	friend class ATower;
	friend class ATDGameModeBase;

private:
	//@��Ī �ø��� �迭 �ּҴ� UnitState * Direction as Byte
	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<class UPaperFlipbook>> Animations;

protected:
	UPROPERTY(EditAnywhere)
	FTowerUpInfo UpTypes[UPGRADES_NUM];
	//TArray<FTowerUpInfo> UpsInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 AttackRange;

	//@Note Per Second
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AHomingProjectile> BulletType;

public:

	//@return nullptr when UpType is not valid.
	UFUNCTION(BlueprintPure)
	UTowerData* GetNextUpgraded(const ETowerType& UpType);

	//@���� Ÿ�Կ��� ������ ���׷��̵� Ʈ��
	UFUNCTION(BlueprintPure)
	UTowerData* GetUpgraded(const TArray<ETowerType>& UpTypeTree);

	//@Note BP��. c++������ TArray�� ī���� �ʿ䰡 ���� ����. see class note
	UFUNCTION(BlueprintPure)
	TArray<FTowerUpInfo> GetUpTypesInfo();

	//@return Animation of current level, direction and state
	UFUNCTION(BlueprintCallable)
	UPaperFlipbook* GetMatchingAnim(const EDirection& Direction, const EUnitState& State);
};

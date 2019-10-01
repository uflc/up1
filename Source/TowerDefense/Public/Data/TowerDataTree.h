// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TDUnitCommonData.h"
#include "TowerDataTree.generated.h"

USTRUCT(BlueprintType)
struct FTowerUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UTowerData* Upgrade;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Preview;
};


//Note TArray with FixedAlloc or c++ fixed array reference BP ������
// https://docs.unrealengine.com/en-us/Programming/Development/CodingStandard#stongly-typedenums ��..
//Ÿ�� Ÿ�� ���׷��̵� Ʈ��
//TODO BlueprintPure or const or FORCEINLINE ??
UCLASS(BlueprintType)
class TOWERDEFENSE_API UTowerData : public UTDUnitCommonData
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FTowerUpInfo UpTypes[UPGRADES_NUM];
	//TArray<FTowerUpInfo> UpsInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector ProjSpawnCompensVec;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText TowerInfoText;

public:
	//@return nullptr when UpType is not valid.
	UFUNCTION(BlueprintPure)
	UTowerData* GetNextUpgraded(const ETowerType& UpType);

	//���� Ÿ�Կ��� ������ ���׷��̵� Ʈ�� not usefull?
	UFUNCTION(BlueprintPure)
	UTowerData* GetUpgraded(const TArray<ETowerType>& UpTypeTree);

	//BP��. c++������ TArray�� ī���� �ʿ䰡 ���� ����. see class note
	UFUNCTION(BlueprintPure)
	TArray<FTowerUpInfo> GetUpTypesInfo();

	//UFUNCTION(BlueprintPure)
	//FText GetTowerInfoText();

	FORCEINLINE FVector GetCompensVec() const { return ProjSpawnCompensVec; }

	FORCEINLINE int32 GetCost() const { return Cost; }
};

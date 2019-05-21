// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDTypes.h"
#include "TowerUpDataTree.generated.h"


//@Note TArray with FixedAlloc or c++ fixed array reference BP 미지원
//@ https://docs.unrealengine.com/en-us/Programming/Development/CodingStandard#stongly-typedenums 흠..
//@타워 타입 업그레이드 트리
//@모든 배열 주소는 타입과 일치해야함.
//@TODO make const or FORCEINLINE ??
UCLASS(BlueprintType)
class UTowerUpData : public UDataAsset
{
	GENERATED_BODY()

friend class ATower;
friend class ATDGameModeBase;

private:
	//@타워 액션메뉴에서 뜰 업그레이드 미리보기 이미지
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<class UTexture2D> UpPreviews[UPGRADES_NUM];

	//@매칭 플립북 배열 주소는 UnitState * Direction as Byte
	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<class UPaperFlipbook>> Animations;

	//@현재 타입에서 가능한 업그레이드 타입
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

	//@현재 타입에서 가능한 업그레이드 트리
	UFUNCTION(BlueprintPure)
	UTowerUpData* GetUpgraded(const TArray<ETowerType>& UpTypes);

	//@Note BP용. c++에서는 TArray에 카피할 필요가 전혀 없다. see class note
	UFUNCTION(BlueprintPure)
	TArray<TSoftObjectPtr<class UTexture2D>> GetUpPreviews();

	//@return Animation of current level, direction and state
	UFUNCTION(BlueprintCallable)
	UPaperFlipbook* GetMatchingAnim(const EDirection& Direction, const EUnitState& State);
};

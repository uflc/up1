// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDTypes.h"
#include "TDUnitCommonData.generated.h"


//@TODO
UCLASS(Blueprintable, BlueprintType)
class UTDUnitCommonData : public UDataAsset
{
	GENERATED_BODY()

	DECLARE_DELEGATE(FLoadCompletedSignature);

protected:
	friend class ATDUnit;
	friend class ATower; //»Ï...
	friend class ATDGameModeBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TDUnit|Property")
	bool IsInitialized;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<TSoftObjectPtr<class UPaperFlipbook>> Animations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float DefaultAttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	class UTDWeaponCommonData* WeaponData;	// or array

public:
	FLoadCompletedSignature OnFlipbooksLoaded;

	UFUNCTION()
	void Initialize();

	UFUNCTION()
	void LoadFlipbooksDeffered();
};

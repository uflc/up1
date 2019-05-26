// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDTypes.h"
#include "TDUnitCommonData.generated.h"


//@TODO
UCLASS(Blueprintable, BlueprintType)
class TOWERDEFENSE_API UTDUnitCommonData : public UDataAsset
{
	GENERATED_BODY()

	DECLARE_DELEGATE(FLoadCompletedSignature);

protected:
	friend class ATDGameModeBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsInitialized;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TArray<TSoftObjectPtr<class UPaperFlipbook>> Animations;

	//UPROPERTY(EditAnywhere, Category = "TDUnit|Property")
	//float DefaultAttackRange;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class UWeaponComponent> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	class UTDWeaponCommonData* WeaponData;	// or array

public:
	FLoadCompletedSignature OnFlipbooksLoaded;

	UFUNCTION()
	void Initialize();

	UFUNCTION()
	void LoadFlipbooksDeffered();

	FORCEINLINE const TArray<TSoftObjectPtr<class UPaperFlipbook>>& GetAnimations() const { return Animations; }
	FORCEINLINE TSubclassOf<UWeaponComponent> GetWeaponClass() const { return WeaponClass; }
	FORCEINLINE UTDWeaponCommonData* GetWeaponData() { return WeaponData; }
};

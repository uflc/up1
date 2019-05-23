// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDTypes.h"
#include "TDWeaponCommonData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TOWERDEFENSE_API UTDWeaponCommonData : public UDataAsset
{
	GENERATED_BODY()

	DECLARE_DELEGATE(FLoadCompletedSignature);

protected:
	friend class UWeaponComponent;
	//friend class TSubclassOf<UWeaponComponent>; //???
	friend class ATDGameModeBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TDUnit|Property")
	bool IsInitialized;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UPaperFlipbook* EffectFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultSplashRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DefaultDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDebuffSet> DebuffSetArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultDebuffChance;

public:
	FLoadCompletedSignature OnFlipbooksLoaded;

	UFUNCTION()
	void Initialize();

	UFUNCTION()
	void LoadFlipbooksDeffered();

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDTypes.h"
#include "TDWeaponCommonData.generated.h"

/**
 * 
 */
class UWeaponComponent;

UCLASS(Blueprintable, BlueprintType)
class TOWERDEFENSE_API UTDWeaponCommonData : public UDataAsset
{
	GENERATED_BODY()

	DECLARE_DELEGATE(FLoadCompletedSignature);

protected:
	friend UWeaponComponent;	
	friend class ATDGameModeBase;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TDUnit|Property")
	//bool IsInitialized;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	//TMap<EWeaponFlipbookType, TSoftObjectPtr<class UPaperFlipbook>> FlipbookMap;

//for a test
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TSubclassOf<UWeaponComponent> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	class UTDProjectileCommonData* ProjectileData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TSoftObjectPtr<class UPaperFlipbook> EffectFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float DefaultSplashRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float DefaultCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float DefaultRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	int DefaultDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	TArray<FDebuffSet> DebuffSetArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float DefaultDebuffChance;

public:
	FLoadCompletedSignature OnFlipbooksLoaded;

	UFUNCTION()
	void Initialize();

	UFUNCTION()
	void LoadFlipbooksDeffered();

	UClass* GetWeaponClass();
};

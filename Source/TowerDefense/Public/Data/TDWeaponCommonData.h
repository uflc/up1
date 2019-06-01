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
	friend class ATDGameModeBase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TDUnit|Property")
	bool IsInitialized;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	//TMap<EWeaponFlipbookType, TSoftObjectPtr<class UPaperFlipbook>> FlipbookMap;

//for a test
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	class UTDProjectileCommonData* ProjectileData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<class AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSoftObjectPtr<class UPaperFlipbook> EffectFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effector")
	float DefaultSplashRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float DefaultCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effector")
	int DefaultDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float DefaultRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effector")
	TArray<FDebuff> DebuffSetArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effector")
	float DefaultDebuffChance;

public:
	FLoadCompletedSignature OnFlipbooksLoaded;

	void Initialize();

	UFUNCTION()
	void LoadFlipbooksDeffered();

	//UClass* GetWeaponClass();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDTypes.h"
#include "TDProjectileCommonData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TOWERDEFENSE_API UTDProjectileCommonData : public UDataAsset
{
	GENERATED_BODY()
	
	DECLARE_DELEGATE(FLoadCompletedSignature);

protected:
	friend class AProjectileBase;
	friend class ATDGameModeBase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsInitialized;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TMap<EWeaponFlipbookType, TSoftObjectPtr<class UPaperFlipbook>> FlipbookMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	bool bIsDirectable;
public:
	FLoadCompletedSignature OnFlipbooksLoaded;

	void Initialize();

	UFUNCTION()
	void LoadFlipbooksDeffered();

};

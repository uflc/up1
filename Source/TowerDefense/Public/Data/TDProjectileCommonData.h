// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDTypes.h"
#include "TDProjectileCommonData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TOWERDEFENSE_API UTDProjectileCommonData : public UDataAsset
{
	GENERATED_BODY()
	
	DECLARE_DELEGATE(FLoadCompletedSignature);

private:
	UPROPERTY(VisibleAnywhere)
	bool bIsInitialized;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EWeaponFlipbookType, TSoftObjectPtr<class UPaperFlipbook>> FlipbookMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<class USoundCue> HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsDirectable;

public:
	FLoadCompletedSignature OnFlipbooksLoaded;

	virtual void PostLoad() override;

	void Initialize();

	UFUNCTION()
	void LoadFlipbooksDeffered();

	FORCEINLINE bool IsInitialzied() const { return bIsInitialized; }
	FORCEINLINE bool IsDirectable() const { return bIsDirectable; }
	FORCEINLINE float GetVelocity() const { return Velocity; }
	FORCEINLINE const TSoftObjectPtr<class USoundCue>& GetHitSound() const { return HitSound; }
	FORCEINLINE const TMap<EWeaponFlipbookType, TSoftObjectPtr<class UPaperFlipbook>>& GetFlipbookMap() const { return FlipbookMap; }
};

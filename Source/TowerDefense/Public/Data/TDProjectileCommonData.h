// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
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

	UPROPERTY(Transient)
	TArray<UPaperFlipbook*> RealFlipbooks;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<class USoundCue> HitSound;

	UPROPERTY(Transient)
	USoundCue* RealHitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsDirectable;

public:
	FLoadCompletedSignature OnLoadCompleted;

	virtual void PostLoad() override;

	void LoadResources();
	UFUNCTION()
	void LoadResourcesDeffered();

	FORCEINLINE bool IsInitialzied() const { return bIsInitialized; }
	FORCEINLINE bool IsDirectable() const { return bIsDirectable; }
	FORCEINLINE float GetVelocity() const { return Velocity; }
	FORCEINLINE const TSoftObjectPtr<class USoundCue>& GetHitSound() const { return HitSound; }
	FORCEINLINE const TMap<EWeaponFlipbookType, TSoftObjectPtr<class UPaperFlipbook>>& GetFlipbookMap() const { return FlipbookMap; }
};

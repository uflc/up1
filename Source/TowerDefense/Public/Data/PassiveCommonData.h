// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "TDTypes.h"
#include "PassiveCommonData.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UPassiveCommonData : public UDataAsset
{
	GENERATED_BODY()
	
	DECLARE_DELEGATE(FLoadCompletedSignature);

private:
	UPROPERTY(VisibleAnywhere)
	bool bIsInitialized;

protected:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	//class UTDProjectileCommonData* ProjectileData;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	//TSubclassOf<class AProjectileBase> ProjectileClass;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	//TSoftObjectPtr<class UPaperFlipbook> HitFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSoftObjectPtr<class USoundCue> SoundEffect;

	UPROPERTY(Transient)
	USoundCue* RealSoundEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float DefaultCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float DefaultAggroRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float DefaultEffectRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FEffectorData EffectorData;

public:
	FLoadCompletedSignature OnLoadCompleted;

	virtual void PostLoad() override;

	void LoadResources();

	UFUNCTION()
	void LoadResourcesDeffered();

	FORCEINLINE bool IsInitialzied() const { return bIsInitialized; }
	FORCEINLINE FEffectorData GetEffectorData() const { return EffectorData; }
	FORCEINLINE int32 GetDefaultDamage() const { return EffectorData.DefaultDamage; }
	FORCEINLINE float GetDefaultSplashRange() const { return EffectorData.DefaultSplashRange; }
	FORCEINLINE float GetDefaultAggroRange() const { return DefaultAggroRange; }
	FORCEINLINE float GetDefaultEffectRange() const { return DefaultEffectRange; }
	FORCEINLINE float GetDefaultCooldown() const { return DefaultCooldown; }
	FORCEINLINE const TArray<FDebuff>& GetDebuffArray() const { return EffectorData.DebuffArray; }
	FORCEINLINE const TSoftObjectPtr<class USoundCue>& GetSoundEffect() { return SoundEffect; }
};

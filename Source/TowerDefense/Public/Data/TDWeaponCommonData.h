// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "TDTypes.h"
#include "TDWeaponCommonData.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class TOWERDEFENSE_API UTDWeaponCommonData : public UDataAsset
{
	GENERATED_BODY()

	DECLARE_DELEGATE(FLoadCompletedSignature);

private:
	UPROPERTY(VisibleAnywhere)
	bool bIsInitialized;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	class UTDProjectileCommonData* ProjectileData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<class AProjectileBase> ProjectileClass;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSoftObjectPtr<class UPaperFlipbook> HitFlipbook;

	UPROPERTY(Transient)
	UPaperFlipbook* RealHitFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSoftObjectPtr<class USoundCue> AttackSound;

	UPROPERTY(Transient)
	USoundCue* RealAttackSound;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float DefaultCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float DefaultRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FEffectorData EffectorData;

public:
	FLoadCompletedSignature OnLoadCompleted;

	virtual void PostLoad() override;

	void LoadResources();
	UFUNCTION()
	void LoadResourcesDeffered();

	FORCEINLINE bool IsInitialzied() const { return bIsInitialized; }
	FORCEINLINE UTDProjectileCommonData* GetProjectileData() const { return ProjectileData; }
	FORCEINLINE TSubclassOf<class AProjectileBase> GetProjectileClass() const { return ProjectileClass; }
	FORCEINLINE FEffectorData GetEffectorData() const { return EffectorData; }
	FORCEINLINE int32 GetDefaultDamage() const { return EffectorData.DefaultDamage; }
	FORCEINLINE float GetDefaultSplashRange() const { return EffectorData.DefaultSplashRange;}
	FORCEINLINE float GetDefaultRange() const { return DefaultRange; }
	FORCEINLINE float GetDefaultCooldown() const { return DefaultCooldown; }
	FORCEINLINE const TArray<FDebuff>& GetDebuffArray() const { return EffectorData.DebuffArray; }
	FORCEINLINE const TSoftObjectPtr<class UPaperFlipbook>& GetHitFlipbook() { return HitFlipbook; }
	FORCEINLINE const TSoftObjectPtr<class USoundCue>& GetAttackSound() { return AttackSound; }
};

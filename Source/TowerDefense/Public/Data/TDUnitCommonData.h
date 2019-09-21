// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "TDUnitCommonData.generated.h"


//TODO
UCLASS(BlueprintType)
class TOWERDEFENSE_API UTDUnitCommonData : public UDataAsset
{
	GENERATED_BODY()

	DECLARE_EVENT(UTDUnitCommonData, FLoadCompletedSignature);

private:
	UPROPERTY(VisibleAnywhere)
	bool bIsInitialized;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TArray<TSoftObjectPtr<class UPaperFlipbook>> Animations;

	UPROPERTY(Transient)
	TArray<UPaperFlipbook*> RealAnims;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	TArray<TSoftObjectPtr<class USoundCue>> Sounds;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class UWeaponComponent> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	class UTDWeaponCommonData* WeaponData;	

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TArray<TSubclassOf<class UWeaponComponent>> SkillClassArr;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TArray<class UTDWeaponCommonData*> SkillDataArr;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TArray<TSubclassOf<class UPassiveSkillComponent>> PassiveSkillClassArr;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TArray<class UPassiveCommonData*> PassiveSkillDataArr;
	
public:
	FLoadCompletedSignature OnLoadCompleted;

	virtual void PostLoad() override;

	UFUNCTION(BlueprintCallable)
	virtual void LoadResources();
	UFUNCTION()
	void LoadResourcesDeffered();

	FORCEINLINE bool IsInitialzied() const { return bIsInitialized; }
	FORCEINLINE const TArray<TSoftObjectPtr<class UPaperFlipbook>>& GetAnimations() const { return Animations; }
	FORCEINLINE const TArray<UPaperFlipbook*>& GetRealAnimations() const { return RealAnims; }
	FORCEINLINE const TArray<TSoftObjectPtr<class USoundCue>>& GetSounds() const { return Sounds; }
	FORCEINLINE TSubclassOf<UWeaponComponent> GetWeaponClass() const { return WeaponClass; }
	FORCEINLINE UTDWeaponCommonData* GetWeaponData() { return WeaponData; }
	FORCEINLINE TArray<TSubclassOf<class UWeaponComponent>> GetSkillClassArr() const { return SkillClassArr; }
	FORCEINLINE TArray<class UTDWeaponCommonData*> GetSkillDataArr() { return SkillDataArr; }
	FORCEINLINE TArray<TSubclassOf<class UPassiveSkillComponent>> GetPassiveClassArr() const { return PassiveSkillClassArr; }
	FORCEINLINE TArray<class UPassiveCommonData*> GetPassiveDataArr() { return PassiveSkillDataArr; }
};

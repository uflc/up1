// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPaperCharacter.h"
#include "Tower.generated.h"

class UPaperFlipbook;
class UPaperFlipbookComponent;

UENUM(BlueprintType)
enum class ETowerState : uint8
{
	TS_Idle UMETA(DisplayName = "Idle"),
	TS_Action  UMETA(DisplayName = "Attack or Open")
};

UENUM(BlueprintType)
enum class ETowerDirectionState : uint8
{
	TDS_LD UMETA(DisplayName = "LT"),
	TDS_LT  UMETA(DisplayName = "LD"),
	TDS_RT UMETA(DisplayName = "RT"),
	TDS_RD  UMETA(DisplayName = "RD"),
};



UCLASS(Abstract, BluePrintable)
class TOWERDEFENSE_API ATower : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATower();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSelected;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	uint8 TowerTypeNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUnitTeam Team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TowerActionDelayCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDelayChecking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETowerState TowerState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETowerDirectionState TowerDirectionState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMyPaperCharacter* AggroTarget;

public:	
	UFUNCTION(BlueprintCallable, Category = "UI|HUD|Tower")
	void OnDeselected();

	UFUNCTION(BlueprintCallable, Category = "UI|HUD|Tower")
	void ShowActionMenu();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI|HUD|Tower")
	virtual FString GetPresetName();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI|HUD|Tower")
	virtual FString GetTowerStatusText();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI|HUD|Tower")
	virtual FString GetTowerDescriptionText();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tower Property")
	virtual float GetTowerRange();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tower Property")
	virtual float GetTowerAttackSpd();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tower Property")
	virtual int32 GetTowerAttackDmg();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ResponseButtonEvent(int iNum);

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationCPP();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	virtual TSoftObjectPtr<UPaperFlipbook> GetFlipbookOfCurrentState();

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void StartAction();

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void ActionExecute();
};

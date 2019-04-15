// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

class UPaperFlipbook;

UENUM(BlueprintType)
enum class ETowerState : uint8
{
	TS_Idle UMETA(DisplayName = "Idle"),
	TS_Action  UMETA(DisplayName = "Attack or Open")
};

UCLASS(Abstract, BluePrintable)
class WORK2_API ATower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATower();

protected:
	uint8 bIsActionMenuDisplayed : 1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	uint8 TowerTypeNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETowerState TowerState;

	//타워의 가능한 업그레이드를 각각 설정해서 그에 따라 위젯을 구성할 경우
	/*UPROPERTY(EditAnywhere, BluePrintReadWrite)
	TArray<TSubclassOf<ATower>> Upgrades;*/

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//static TMap<ETowerState, TArray<TSoftObjectPtr<UPaperFlipbook>>> FlipbookMap;

	// Actor OnClicked Signature delegate // use if c++ only
	//void Selected(AActor* TouchedActor, FKey ButtonPressed);

	////////////////////// UI ///////////////////////
	UFUNCTION(BlueprintCallable, Category = "UI|HUD")
	virtual void ShowActionMenu();
	UFUNCTION(BlueprintCallable, Category = "UI|HUD")
	virtual void HideActionMenu();
	// Unused

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Texture")
	void ResetMaterial(); // will be changed to ChangeSprite("");

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI|HUD")
	virtual FString GetPresetName();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI|HUD")
	virtual FString GetTowerStatusText();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI|HUD")
	virtual FString GetTowerDescriptionText();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI|HUD")
	virtual float GetTowerRange();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI|HUD")
	virtual float GetTowerAttackSpd();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI|HUD")
	virtual float GetTowerAttackDmg();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ResponseButtonEvent(int iNum);

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationCPP();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	TSoftObjectPtr<UPaperFlipbook> GetFlipbookOfCurrentState();
};

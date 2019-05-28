// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "TDGameModeBase.generated.h"

/**
 ���ҽ� �ε� �� ����� ���� ����
 */
UCLASS()
class TOWERDEFENSE_API ATDGameModeBase : public AGameModeBase
{										
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFullyLoadedDelegate);

public:
	/** Remove the current menu widget and create a new one from the specified class, if provided. */
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "UI")
	UUserWidget* GetCurrentWidget();

	UPROPERTY(BlueprintAssignable, Category = "TDUnit")
	FFullyLoadedDelegate OnAllTDUnitFlipbooksLoaded;

protected:
	/** Called when the game starts. */
	virtual void BeginPlay() override;

	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	/** The widget instance that we are using as our menu. */
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* CurrentWidget;

	////@ TD ���� ������. Ư�� �ʵ� ������ �ø���. //TODO Config
	//UPROPERTY(EditAnywhere, Category = "TDUnit")
	//TArray<class UTDUnitCommonData*> TDUnitCommons;

	//@TODO �� ���� �ε� ���
	UFUNCTION(BlueprintCallable, Category = "TDUnit")
	void LoadTDUnitCommons(const TArray<TSoftObjectPtr<UTDUnitCommonData>>& InUsingTDUnitCommons);

	int8 UnloadedTDUnitCommonNum;

	//BaseTowerData�κ��� ��� Ÿ�� �����Ϳ� ������ �� �ֱ� ������ �ϴ� �̷��� ��.
	UFUNCTION(BlueprintCallable, Category = "TDUnit")
	void LoadTowerResources(UTowerData * InTowerDataTree);
	void LoadTowerResourcesDeffered();

public:	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI|HUD")
	void ChangeTower(class ATower* InInteractingTower, TSubclassOf<ATower> NewTowerClass);

	void OnTDUnitFlipbooksLoaded();

};

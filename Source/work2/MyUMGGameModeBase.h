// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h" //need? auto
#include "GameFramework/GameModeBase.h"
#include "MyUMGGameModeBase.generated.h"
class ATower;
/**
 * Like GameManager
 */
UCLASS()
class WORK2_API AMyUMGGameModeBase : public AGameModeBase
{										
	GENERATED_BODY()

public:
	/** Remove the current menu widget and create a new one from the specified class, if provided. */
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	UUserWidget* GetCurrentWidget();

	//UFUNCTION(BlueprintCallable)
	//UUserWidget* GetTowerWidget();

protected:
	/** Called when the game starts. */
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI|HUD")
	void ChangeTower(ATower* InInteractingTower, TSubclassOf<ATower> NewTowerClass);

	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	/** The widget instance that we are using as our menu. */
	UPROPERTY()
	UUserWidget* CurrentWidget;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UUserWidget* TowerWidget;


};

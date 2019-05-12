// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "MyUMGGameModeBase.generated.h"

class ATower;
class UTDUnitCommonData;


/**
 GameManager
 적절한 이름 필요.
 리소스 로드 및 사용할 위젯 관리
 */
UCLASS()
class WORK2_API AMyUMGGameModeBase : public AGameModeBase
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit")
	TArray<UTDUnitCommonData*> TDUnitCommons;

	UFUNCTION(BlueprintCallable, Category = "TDUnit")
	void LoadTDUnitCommons(UPARAM(ref) TArray<TSoftObjectPtr<UTDUnitCommonData>>& InUsingTDUnitCommons);

	int8 UnloadedTDUnitCommonNum;

public:	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI|HUD")
	void ChangeTower(ATower* InInteractingTower, TSubclassOf<ATower> NewTowerClass);

	void OnTDUnitFlipbooksLoaded();

};

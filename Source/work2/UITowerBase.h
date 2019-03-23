// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UITowerBase.generated.h"

/**
 * 
 */

class UCanvasPanel;
class ATower;

UCLASS()
class WORK2_API UUITowerBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UCanvasPanel* Root;

	UPROPERTY(BlueprintReadWrite)
	ATower* OwnTower;

public:
	ATower* __native_GetOwnTower(){return OwnTower;}

	UFUNCTION(BlueprintCallable)
	bool SelectPreset(FString iName);

	UFUNCTION(BlueprintCallable)
	bool SetButtonsEvent();

	UFUNCTION()
	void CloseUI();
};

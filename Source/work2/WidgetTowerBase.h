// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetTowerBase.generated.h"

/**
 * 
 */

class UCanvasPanel;
class ATower;

UCLASS()
class WORK2_API UWidgetTowerBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UCanvasPanel* Root;

	UPROPERTY(BlueprintReadWrite)
	ATower* OwnTower;
public:
	UFUNCTION(BlueprintCallable)
	bool SelectPreset(FString iName);
};

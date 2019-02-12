// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "UITowerButton.generated.h"

class UUITowerBase;

/**
 * 
 */
UCLASS()
class WORK2_API UUITowerButton : public UButton
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite)
	UUITowerBase* RootWidget;
public:
	UFUNCTION()
	void ButtonEvent();

	void __native_SetRootCanvas(UUITowerBase* iWidget){ RootWidget = iWidget;}
};

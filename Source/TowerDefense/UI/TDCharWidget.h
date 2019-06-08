// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDCharWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDCharWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly)
	class ATDCharacter* Owner;

	UFUNCTION(BlueprintImplementableEvent)
	void PostSetOwner();

public:
	UFUNCTION(BlueprintCallable)
	void SetOwner(ATDCharacter* NewOwner);
};

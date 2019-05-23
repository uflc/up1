// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "SimpleFlipbookEffect.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ASimpleFlipbookEffect : public APaperFlipbookActor
{
	GENERATED_BODY()
	
public:
	void SetupEffect(class UPaperFlipbook* inFlipbook);
};

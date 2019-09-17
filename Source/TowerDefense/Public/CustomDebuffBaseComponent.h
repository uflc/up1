// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "TDTypes.h"
#include "PaperFlipbookComponent.h"
#include "CustomDebuffBaseComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom) )
class TOWERDEFENSE_API UCustomDebuffBaseComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UCustomDebuffBaseComponent();
	//UCustomDebuffBaseComponent(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// BlueprintNativeEvent for testing
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DebuffStart();

	virtual void DebuffStart_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DebuffEnd();

	virtual void DebuffEnd_Implementation();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "TDTypes.h"
#include "CustomDebuffBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UCustomDebuffBaseComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCustomDebuffBaseComponent();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTDPaperFlipbookComponent* EffectFlipbook;

	// Called when the game starts
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void DebuffStart();

	virtual void DebuffEnd();
};

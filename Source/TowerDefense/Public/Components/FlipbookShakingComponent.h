// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlipbookShakingComponent.generated.h"

class UPaperFlipbookComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UFlipbookShakingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFlipbookShakingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float ShakePower;
	float ShakeDuration;
	UPaperFlipbookComponent* Flipbook;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Initialize(float iShakePower, float iShakeDuration);
};

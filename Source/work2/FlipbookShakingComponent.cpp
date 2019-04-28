// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipbookShakingComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework\Actor.h"

// Sets default values for this component's properties
UFlipbookShakingComponent::UFlipbookShakingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	ShakePower=0;
	ShakeDuration=0;
	Flipbook=nullptr;
}


// Called when the game starts
void UFlipbookShakingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UFlipbookShakingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if(!Flipbook) { DestroyComponent(); return; }
	ShakeDuration-=DeltaTime;
	if (ShakeDuration < 0)
	{
		Flipbook->SetRelativeLocation(FVector::ZeroVector);
		DestroyComponent();
		return;
	}

	FVector ShakeVector;
	ShakeVector.X = FMath::FRandRange(-50, 50);
	ShakeVector.Y = FMath::FRandRange(-50, 50);
	ShakeVector.Z = 0;

	ShakeVector.Normalize();
	ShakeVector*=ShakePower;

	Flipbook->SetRelativeLocation(ShakeVector);
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFlipbookShakingComponent::Initialize(float iShakePower, float iShakeDuration)
{
	ShakePower= iShakePower; 
	ShakeDuration=iShakeDuration; 
	Flipbook = Cast<UPaperFlipbookComponent>(GetOwner()->GetComponentByClass(UPaperFlipbookComponent::StaticClass()));
}


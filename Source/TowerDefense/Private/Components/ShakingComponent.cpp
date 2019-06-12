// Fill out your copyright notice in the Description page of Project Settings.


#include "ShakingComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework\Actor.h"
#include "TowerDefense.h"

UShakingComponent::UShakingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ShakePower    = 0.0f;
	ShakeDuration = 0.0f;
}


// Called every frame
void UShakingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!ShakingScene)
	{ 
		TD_LOG(Warning, TEXT("No Scene!"));
		DestroyComponent(); 
		return; 
	}

	ShakeDuration -= DeltaTime;
	if (ShakeDuration <= 0.0f)
	{
		DestroyComponent();
		return;
	}

	FVector ShakeVector;
	ShakeVector.X = FMath::FRandRange(-50.0f, 50.0f);
	ShakeVector.Y = FMath::FRandRange(-50.0f, 50.0f);
	ShakeVector.Z = 0.0f;

	ShakeVector.Normalize();
	ShakeVector *= ShakePower;

	ShakingScene->AddLocalOffset(ShakeVector);
}

void UShakingComponent::Initialize(float InShakePower, float InShakeDuration, USceneComponent* InShakingScene)
{
	if (InShakePower == 0.0f || InShakeDuration == 0.0f)
	{
		DestroyComponent();
		return;
	}

	if (InShakingScene)
	{
		ShakingScene = InShakingScene;
	}
	else if (!ShakingScene)
	{
		//No valid explicit scene. so see if owner or outer root component is valid scence.
		AActor* Owner = GetOwner();
		if (!Owner)
		{
			//if No Owner nor Outer, we cannnot decide scene.
			UObject* Outer = GetOuter();
			if (!Outer)
			{
				DestroyComponent();
				return;
			}

			Owner = Cast<AActor>(Outer);
			if (!Owner)
			{
				USceneComponent* RootScene = Cast<USceneComponent>(Outer);
				if (!RootScene)
				{
					DestroyComponent();
					return;
				}

				ShakingScene = RootScene;
			}
		}

		if (Owner)
		{
			ShakingScene = Owner->GetRootComponent();
		}
	}

	if (!bRegistered)
	{
		RegisterComponent();
	}

	ShakePower    = InShakePower; 
	ShakeDuration = InShakeDuration; 
}

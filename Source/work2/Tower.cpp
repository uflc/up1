// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "work2.h"
#include "MyUMGGameModeBase.h" //test


// Sets default values
ATower::ATower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	OnClicked.AddDynamic(this, &ATower::Selected);
} 

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATower::Selected(AActor * TouchedActor, FKey ButtonPressed)
{
	ShowActionMenu();
}

void ATower::ShowActionMenu()
{
	if (bIsActionMenuDisplayed) return;

	//ActionMenu is not displayed now

	//Cast<AMyUMGGameModeBase>(GEngine->GetWorld()->GetAuthGameMode())->GetCurrentWidget()

}

void ATower::HideActionMenu()
{
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


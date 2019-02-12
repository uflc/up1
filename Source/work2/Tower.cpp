// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "MyUMGGameModeBase.h" //test
#include "Engine/Engine.h"
#include "HUDWidget.h"


// Sets default values
ATower::ATower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//use if c++ only
	//OnClicked.AddDynamic(this, &ATower::Selected);
} 

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATower::ShowActionMenu()
{
	//if (bIsActionMenuDisplayed) return;

	////to use GEngine include engine/engine.h not public engine.h for iwyu
	//UHUDWidget* HUDWidget = Cast<UHUDWidget>(GEngine->GetWorld()->GetAuthGameMode<AMyUMGGameModeBase>()->GetCurrentWidget());
	//HUDWidget->ShowTowerActionMenu(this);

	//bIsActionMenuDisplayed = true;
}

void ATower::HideActionMenu()
{
	//if (!bIsActionMenuDisplayed) return;

	//UHUDWidget* HUDWidget = Cast<UHUDWidget>(GEngine->GetWorld()->GetAuthGameMode<AMyUMGGameModeBase>()->GetCurrentWidget());
	//HUDWidget->HideTowerActionMenu();

	//bIsActionMenuDisplayed = false;
}

FString ATower::GetPresetName()
{
	return FString();
}

void ATower::ResponseButtonEvent(int iNum)
{
	switch (iNum)
	{
	case 0:
	return;
		default:
		return;
	}
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


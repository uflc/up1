// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerEmpty.h"
#include "UITowerBase.h"
#include "MyUMGGameModeBase.h"
#include "Engine.h"
ATowerEmpty::ATowerEmpty()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnClicked.AddDynamic(this, &ATowerEmpty::Selected);
}

// Called when the game starts or when spawned
void ATowerEmpty::BeginPlay()
{
	Super::BeginPlay();

}

void ATowerEmpty::Selected(AActor * TouchedActor, FKey ButtonPressed)
{
	ShowActionMenu();
	// PlaySoundEffect();
}

void ATowerEmpty::ShowActionMenu()
{
	//if (bIsActionMenuDisplayed) return;

	//ActionMenu is not displayed now

	//auto widget = Cast<AMyUMGGameModeBase>(GEngine->GetWorld()->GetAuthGameMode())->GetCurrentWidget()

	// TODO :: Complete this
	//auto towerwidget = Cast<UWidgetTowerBase>(Cast<AMyUMGGameModeBase>(GEngine->GetWorld()->GetAuthGameMode())->GetTowerWidget());
	//towerwidget->SelectPreset("Empty");
}

void ATowerEmpty::HideActionMenu()
{
}

FString ATowerEmpty::GetPresetName()
{
	return "Empty";
}

void ATowerEmpty::ResponseButtonEvent(int iNum)
{
	switch (iNum)
	{
	case 0:
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "Button 0");
		return;
	default:
		return;
	}
}

// Called every frame
void ATowerEmpty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
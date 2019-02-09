// Fill out your copyright notice in the Description page of Project Settings.

//#include "work2.h" //need?
#include "MyUMGPlayerController.h"

void AMyUMGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}
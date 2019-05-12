// Fill out your copyright notice in the Description page of Project Settings.

#include "TDPlayerController.h"

void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}
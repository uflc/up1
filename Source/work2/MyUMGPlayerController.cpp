// Fill out your copyright notice in the Description page of Project Settings.

//#include "work2.h" //need?
#include "MyUMGPlayerController.h"
#include "Engine.h"
#include "Camera/CameraComponent.h"


void AMyUMGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}

void AMyUMGPlayerController::SetOrthographicCamera()
{
	UCameraComponent* MyCameraComponent = nullptr;

	//MyCameraComponent=PlayerCameraManager->FindComponentByClass<UCameraComponent>();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundActors);
	if (FoundActors.Num() != 0)
		MyCameraComponent = FoundActors[0]->FindComponentByClass<UCameraComponent>();

	if (!MyCameraComponent) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, "NoCameraComponent");
		return;
	}

	MyCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	MyCameraComponent->OrthoWidth = 2048.0f;

	//PlayerCameraManager->bIsOrthographic=true;
	//PlayerCameraManager->SetOrthoWidth(2048.0f);
	//PlayerCameraManager->Camera
}
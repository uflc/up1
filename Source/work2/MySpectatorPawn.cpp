// Fill out your copyright notice in the Description page of Project Settings.

#include "MySpectatorPawn.h"

void AMySpectatorPawn::MoveRight(float AxisVal)
{
}

AMySpectatorPawn::AMySpectatorPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//Create components

	/*RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 50.0f, 0.0f), FRotator(0.0f, 0.0f, -90.0f));
	CameraSpringArm->TargetArmLength = 400.f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 3.0f;*/

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	//Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	//Take control of the default Player
	//AutoPossessPlayer = EAutoReceiveInput::Player0;
}


void AMySpectatorPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMySpectatorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMySpectatorPawn::SetupPlayerInputComponent(UInputComponent * InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
//#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MySpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class WORK2_API AMySpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

	void MoveRight(float AxisVal);

public:
	AMySpectatorPawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
protected:
	UPROPERTY(EditAnywhere)
	//class USpringArmComponent* CameraSpringArm;
	class UCameraComponent* Camera;

	FVector2D CameraInput;
};

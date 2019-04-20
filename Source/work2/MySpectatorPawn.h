// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
//#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MySpectatorPawn.generated.h"

/**
 * 
 현재 level BP가 하고있는 카메라 관련 일을 이 클래스에게 맡길 예정.
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

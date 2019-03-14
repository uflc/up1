// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //need? auto
#include "GameFramework/PlayerController.h"
#include "MyUMGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WORK2_API AMyUMGPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetOrthographicCamera();
};

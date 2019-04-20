// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyUMGPlayerController.generated.h"

/**
 * 
 이름 바꿔야될듯 겜 이름 약칭 정해지면.
 */
UCLASS()
class WORK2_API AMyUMGPlayerController : public APlayerController
{
	GENERATED_BODY()

	//카메라를 이 클래스를 이용해서 다룰 수 있으면 MySpectatorPawn을 사용하지 않을 것.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetOrthographicCamera();
};

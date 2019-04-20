// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyUMGPlayerController.generated.h"

/**
 * 
 �̸� �ٲ�ߵɵ� �� �̸� ��Ī ��������.
 */
UCLASS()
class WORK2_API AMyUMGPlayerController : public APlayerController
{
	GENERATED_BODY()

	//ī�޶� �� Ŭ������ �̿��ؼ� �ٷ� �� ������ MySpectatorPawn�� ������� ���� ��.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetOrthographicCamera();
};

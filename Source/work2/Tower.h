// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"


UCLASS(Abstract, BluePrintable)
class WORK2_API ATower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATower();

protected:

	uint8 bIsActionMenuDisplayed : 1;

	//Ÿ���� ������ ���׷��̵带 ���� �����ؼ� �׿� ���� ������ ������ ���
	/*UPROPERTY(EditAnywhere, BluePrintReadWrite)
	TArray<TSubclassOf<ATower>> Upgrades;*/

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Actor OnClicked Signature delegate // use if c++ only
	//void Selected(AActor* TouchedActor, FKey ButtonPressed);

	////////////////////// UI ///////////////////////
	virtual void ShowActionMenu();
	virtual void HideActionMenu();


	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};

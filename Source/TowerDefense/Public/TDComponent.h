// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDComponent.generated.h"

UCLASS(Blueprintable, Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UTDComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTDComponent();

protected:
	TArray<class UTDSubComponent*> SubComponents;

public:	
	void AddSubComponent(UTDSubComponent* inComp);
	
	void AddSubComponent(UClass* inClass);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDSubComponent.generated.h"


UCLASS(Blueprintable, Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UTDSubComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTDSubComponent();

protected:
	class UTDComponent* Parent;

public:	
	void SetParent(UTDComponent* iComp){ Parent=iComp; }
	UTDComponent* GetParent() { return Parent; }
};

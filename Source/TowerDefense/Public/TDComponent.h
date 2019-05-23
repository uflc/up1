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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<class UTDComponent*> SubComponents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTDComponent* Parent;

public:	
	UFUNCTION(BlueprintCallable)
	virtual void Work(){}

	void SetParent(UTDComponent* iComp) { Parent = iComp; }

	void AddSubComponent(UTDComponent* inComp);
	
	void AddSubComponent(UClass* inClass);

	UTDComponent* GetParent() const { return Parent; }

	UTDComponent* GetSubComponent(const TSubclassOf<UTDComponent> ComponentClass) const;

	TArray<UTDComponent*> GetSubComponentsByClass(TSubclassOf<UTDComponent> ComponentClass) const;
};

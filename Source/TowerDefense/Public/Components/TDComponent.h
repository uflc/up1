// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDComponent.generated.h"

UCLASS(Blueprintable, Abstract, ClassGroup = (Custom))
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
	//UFUNCTION(BlueprintCallable)
	//virtual void Work(){}

	void SetParent(UTDComponent* InParentComp) { Parent = InParentComp; }

	//void AddSubComponent(UTDComponent* inComp);
	
	template <typename  T>
	T* AddSubComponent();

	UTDComponent* GetParent() const { return Parent; }

	UTDComponent* GetSubComponent(const TSubclassOf<UTDComponent> ComponentClass) const;

	TArray<UTDComponent*> GetSubComponentsByClass(const TSubclassOf<UTDComponent> ComponentClass) const;
};


template <typename  T>
inline T* UTDComponent::AddSubComponent()
{
	T*  SubComp = NewObject<T>(this);

	if(!SubComp) return nullptr;
	SubComp->SetParent(this);
	SubComponents.Add(SubComp);

	return SubComp;
}

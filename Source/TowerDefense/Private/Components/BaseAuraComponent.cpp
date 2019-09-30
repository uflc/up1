// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAuraComponent.h"
#include "Components\BoxComponent.h"

void UBaseAuraComponent::Initialize_Implementation()
{
	Super::Initialize_Implementation();

	BoxCollision->RegisterComponent();
	BoxCollision->SetWorldLocation(GetOwner()->GetActorLocation());
	BoxCollision->SetBoxExtent(FVector(EffectRange*1.25,EffectRange,200));
}

void UBaseAuraComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//	BoxCollision->DestroyComponent();
}

UBaseAuraComponent::UBaseAuraComponent()
{
	//FString name = FString(TEXT("Area"));
	//name.AppendInt(rand()%100);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Area0"));
}

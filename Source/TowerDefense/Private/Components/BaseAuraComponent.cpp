// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAuraComponent.h"
#include "Components\BoxComponent.h"

void UBaseAuraComponent::Initialize_Implementation()
{
	BoxCollision->SetWorldScale3D(FVector(500.0f,500.0f,500.0f));
}

UBaseAuraComponent::UBaseAuraComponent()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Area0"));
	BoxCollision->RegisterComponent();
	BoxCollision->SetVisibility(true);
}

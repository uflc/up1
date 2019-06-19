// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionalTower.h"
#include "Components/DirTDPaperFlipbookComponent.h"

ADirectionalTower::ADirectionalTower(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UDirTDPaperFlipbookComponent>(ATDUnit::AnimationComponentName))
{
}
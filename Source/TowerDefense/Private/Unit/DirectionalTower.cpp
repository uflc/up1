// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionalTower.h"
#include "Components/DirTDPaperFlipbookComponent.h"
#include "ProjectileWeaponComponent.h"

ADirectionalTower::ADirectionalTower(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UDirTDPaperFlipbookComponent>(ATDUnit::AnimationComponentName))
{
}

void ADirectionalTower::SetFlipbooks()
{
	Super::SetFlipbooks();

	UProjectileWeaponComponent* Launcher = Cast<UProjectileWeaponComponent>(WeaponComp);
	if (Launcher)
	{
		Launcher->ProjectileRelativeSpawnPoint = Animation->RelativeLocation;
		Launcher->ProjectileRelativeSpawnPoint.Z += 1.0f;
	}
}

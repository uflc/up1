// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionalTower.h"
#include "Components/DirTDPaperFlipbookComponent.h"
#include "ProjectileWeaponComponent.h"
#include "TowerDefense.h"

ADirectionalTower::ADirectionalTower(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UDirTDPaperFlipbookComponent>(ATDUnit::AnimationComponentName))
{
}

void ADirectionalTower::SetFlipbooks()
{
	Super::SetFlipbooks();

	UProjectileWeaponComponent* Launcher = Cast<UProjectileWeaponComponent>(AttackComp);
	if (Launcher)
	{
		Launcher->ProjectileRelativeSpawnPoint = Animation->RelativeLocation;
		Launcher->ProjectileRelativeSpawnPoint.Z += 1.0f;
		TD_LOG(Warning, TEXT("LaunchPoint: %s"), *Launcher->ProjectileRelativeSpawnPoint.ToString());
	}
}

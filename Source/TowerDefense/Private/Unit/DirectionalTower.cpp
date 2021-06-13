// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionalTower.h"
#include "Components/DirTDPaperFlipbookComponent.h"
#include "ProjectileWeaponComponent.h"
#include "TowerDataTree.h"

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
		UTowerData* TowerData = Cast<UTowerData>(UnitData);

		Launcher->ProjectileRelativeSpawnPoint = Animation->GetRelativeLocation() + TowerData->GetCompensVec();
		Launcher->ProjectileRelativeSpawnPoint.Z += 1.0f;
	}
}

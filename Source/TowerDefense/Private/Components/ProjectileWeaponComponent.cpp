// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeaponComponent.h"
#include "ProjectileBase.h"
#include "TDWeaponCommonData.h"
#include "EffectorComponent.h"
#include "TDProjectileCommonData.h"


void UProjectileWeaponComponent::UseWeapon()
{
	if (!IsTargetLocked()) return;
	
	Super::UseWeapon();

<<<<<<< HEAD
	const FVector ProjectileSpawnPoint = GetOwner()->GetActorLocation() + ProjectileRelativeSpawnPoint;
	AProjectileBase* SpawnedProjectile = (AProjectileBase*) GetWorld()->SpawnActor(WeaponData->GetProjectileClass(), &ProjectileSpawnPoint);
=======
	const FVector ProjectileSpawnPoint = GetOwner()->GetActorLocation() + ProjectileRelativeSpawnPoint + FVector(0,0,1.0f);
	AProjectileBase* SpawnedProjectile = (AProjectileBase*) GetWorld()->SpawnActor(WeaponData->ProjectileClass, &ProjectileSpawnPoint);
>>>>>>> 59c378630c1b79a7f50c94dbb4d9575d92a490a0

	SpawnedProjectile->SetTarget(Target);
	SpawnedProjectile->SetCommonData(WeaponData->GetProjectileData(), WeaponData->GetEffectorData(), true);
}

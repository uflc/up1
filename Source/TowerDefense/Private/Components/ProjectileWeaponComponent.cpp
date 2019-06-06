// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeaponComponent.h"
#include "ProjectileBase.h"
#include "TDWeaponCommonData.h"
#include "TDProjectileCommonData.h"
#include "TowerDefense.h"

void UProjectileWeaponComponent::UseWeapon()
{
	if (!IsTargetLocked()) return;
	
	TD_LOG_CALLONLY(Warning);

	const FVector ProjectileSpawnPoint = GetOwner()->GetActorLocation() + ProjectileRelativeSpawnPoint;
	AProjectileBase* SpawnedProjectile = (AProjectileBase*) GetWorld()->SpawnActor(WeaponData->ProjectileClass, &ProjectileSpawnPoint);

	SpawnedProjectile->SetCommonData(WeaponData->ProjectileData);
	SpawnedProjectile->SetTarget(Target);
	SpawnedProjectile->SetEffector(WeaponData->DefaultSplashRange, WeaponData->DefaultDamage);
	SpawnedProjectile->SetEffector(WeaponData->DebuffArray);
}

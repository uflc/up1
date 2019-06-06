// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeaponComponent.h"
#include "ProjectileBase.h"
#include "TDWeaponCommonData.h"
#include "TDProjectileCommonData.h"


void UProjectileWeaponComponent::UseWeapon()
{
	if (!IsTargetLocked()) return;
	
	const FVector ProjectileSpawnPoint = GetOwner()->GetActorLocation() + ProjectileRelativeSpawnPoint;
	AProjectileBase* SpawnedProjectile = (AProjectileBase*) GetWorld()->SpawnActor(WeaponData->ProjectileClass, &ProjectileSpawnPoint);

	SpawnedProjectile->SetTarget(Target);
	SpawnedProjectile->SetCommonData(WeaponData->ProjectileData);
	SpawnedProjectile->SetEffector(WeaponData->DefaultSplashRange, WeaponData->DefaultDamage);
	SpawnedProjectile->SetEffector(WeaponData->DebuffArray);
}

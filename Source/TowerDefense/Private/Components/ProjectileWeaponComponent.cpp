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

	const FVector ProjectileSpawnPoint = GetOwner()->GetActorLocation() + ProjectileRelativeSpawnPoint;
	AProjectileBase* SpawnedProjectile = (AProjectileBase*) GetWorld()->SpawnActor(WeaponData->GetProjectileClass(), &ProjectileSpawnPoint);

	SpawnedProjectile->SetTarget(Target);
	SpawnedProjectile->SetCommonData(WeaponData->GetProjectileData(), WeaponData->GetEffectorData(), true);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeaponComponent.h"
#include "ProjectileBase.h"
#include "TDCharacter.h"
#include "EffectorComponent.h"
#include "TDWeaponCommonData.h"
#include "TDProjectileCommonData.h"
#include "AIController.h"
#include "BehaviorTree\BlackboardComponent.h"


void UProjectileWeaponComponent::UseWeapon()
{
	if (TargetValidCheck())
	{
		FVector CaculatedSpawnPoint = GetOwner()->GetActorLocation() + ProjectileRelativeSpawnPoint;

		AProjectileBase* SpawnedProjectile = (AProjectileBase*) GetWorld()->SpawnActor(WeaponData->ProjectileClass, &CaculatedSpawnPoint);

		TArray<UTDComponent*> Effectors = GetSubComponentsByClass(UEffectorComponent::StaticClass());
		for (const auto& Effector : Effectors) // 문제있음
		{
			UEffectorComponent* CopyEffector = DuplicateObject<UEffectorComponent>((UEffectorComponent*)Effector, SpawnedProjectile);
			SpawnedProjectile->AddOwnedComponent(/*(UEffectorComponent*)*/CopyEffector);
		}

		SpawnedProjectile->SetCommonData(WeaponData->ProjectileData);
		SpawnedProjectile->SetTarget(Target);
		SpawnedProjectile->Initialize();

	}
}

//void UProjectileWeaponComponent::InitializeWeaponComp()
//{
//	Super::InitializeWeaponComp();
//
//	// Additional Work
//}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeaponComponent.h"
#include "ProjectileBase.h"
#include "TDCharacter.h"
#include "EffectorComponent.h"
#include "TDWeaponCommonData.h"
#include "TDProjectileCommonData.h"
//#include "Tower.h"
#include "AIController.h"
#include "BehaviorTree\BlackboardComponent.h"

UProjectileWeaponComponent::UProjectileWeaponComponent():ProjectileRelativeSpawnPoint(FVector(0,0,0)), ProjectileisDirectable(false)
{

}

void UProjectileWeaponComponent::BeginPlay(){
}
void UProjectileWeaponComponent::UseWeapon()
{
	if(TargetValidCheck())
	{
		//TSubclassOf<AProjectileBase> ProjectileClass = WeaponCommon->ProjectileClass;

		//if(!Data->IsValidLowLevelFast())return; 

		//if (!Data->ProjectileClass->IsValidLowLevelFast())return;

		FVector CaculatedSpawnPoint = GetOwner()->GetActorLocation() + ProjectileRelativeSpawnPoint;

		AProjectileBase* SpawnedProjectile = (AProjectileBase*)GetWorld()->SpawnActor(WeaponCommon->ProjectileClass, &CaculatedSpawnPoint);

		TArray<UTDComponent*> Effectors = GetSubComponentsByClass(UEffectorComponent::StaticClass());
		for (const auto& Effector : Effectors) // 문제있음
		{
			
			UEffectorComponent* CopyEffector = DuplicateObject<UEffectorComponent>((UEffectorComponent*)Effector, SpawnedProjectile);
			//NewObject<UTDComponent>(Local_Bullet, Effector->StaticClass());
			SpawnedProjectile->AddOwnedComponent(/*(UEffectorComponent*)*/CopyEffector);
		}

		SpawnedProjectile->SetCommonData(WeaponCommon->ProjectileData);
		SpawnedProjectile->SetTarget(vTarget);
		SpawnedProjectile->Initialize();

	}
}

//void UProjectileWeaponComponent::InitializeWeaponComp()
//{
//	Super::InitializeWeaponComp();
//
//	// Additional Work
//}

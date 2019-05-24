// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeaponComponent.h"
#include "BulletBase.h"
#include "TDCharacter.h"
#include "EffectorComponent.h"
//#include "Tower.h"
#include "AIController.h"
#include "AIModule\Classes\BehaviorTree\BlackboardComponent.h"

UProjectileWeaponComponent::UProjectileWeaponComponent():ProjectileRelativeSpawnPoint(FVector(0,0,0)), ProjectileisDirectable(false)
{
}


void UProjectileWeaponComponent::ExecAttack(ATDCharacter* Target)
{
	if (Target->IsValidLowLevelFast() && GetOwner()->IsValidLowLevelFast()) {

		FVector CaculatedSpawnPoint=GetOwner()->GetActorLocation()+ProjectileRelativeSpawnPoint;

		ABulletBase* Local_Bullet = (ABulletBase*)GetWorld()->SpawnActor(ProjectileClass.Get(), &CaculatedSpawnPoint);

		Local_Bullet->Initialize(Target, Damage, ProjectileisDirectable, SplashRange);

	}
}

void UProjectileWeaponComponent::UseWeapon()
{
	if(TargetValidCheck())
	{
		auto CaculatedSpawnPoint = GetOwner()->GetActorLocation() + ProjectileRelativeSpawnPoint;

		auto Local_Bullet = (ABulletBase*)GetWorld()->SpawnActor(ProjectileClass.Get(), &CaculatedSpawnPoint);

		auto Effectors = GetSubComponentsByClass(UEffectorComponent::StaticClass());
		for (auto Effector : Effectors)
		{
			Local_Bullet->AddOwnedComponent(Effector);
		}

		Local_Bullet->Initialize(vTarget, Damage, ProjectileisDirectable, SplashRange);

	}
}

inline void UProjectileWeaponComponent::InitializeProjectileAttackComp()
{
	UWeaponComponent::InitializeWeaponComp();

	// Additional Work
}

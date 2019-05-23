// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeaponComponent.h"
#include "BulletBase.h"
#include "TDCharacter.h"
<<<<<<< HEAD


void URangedAttackComponent::ExecAttack(UObject * Target)
=======
//#include "Tower.h"
#include "AIController.h"
#include "AIModule\Classes\BehaviorTree\BlackboardComponent.h"

UProjectileWeaponComponent::UProjectileWeaponComponent():ProjectileRelativeSpawnPoint(FVector(0,0,0)), ProjectileisDirectable(false)
{
}


<<<<<<< HEAD:Source/TowerDefense/Private/ProjectileWeaponComponent.cpp
void UProjectileWeaponComponent::ExecAttack(ATDCharacter* Target)
=======
void URangedAttackComponent::ExecAttack(ATDCharacter* Target)
>>>>>>> 9dbd6eed48176c0144435ed0a4729a740d1f2351
>>>>>>> origin/master:Source/TowerDefense/Private/RangedAttackComponent.cpp
{
	if (Target->IsValidLowLevelFast() && GetOwner()->IsValidLowLevelFast()) {

		FVector CaculatedSpawnPoint=GetOwner()->GetActorLocation()+ProjectileRelativeSpawnPoint;

		ABulletBase* Local_Bullet = (ABulletBase*)GetWorld()->SpawnActor(ProjectileClass.Get(), &CaculatedSpawnPoint);

		Local_Bullet->Initialize(Target, ((ATDUnit*)GetOwner())->AttackDamage, ProjectileisDirectable, AffectRange);

	}
}

void UProjectileWeaponComponent::Work()
{
	ATDCharacter* Target = (ATDCharacter*)((AAIController*)((ATDUnit*)GetOwner())->GetController())->GetBlackboardComponent()->GetValueAsObject(FName(TEXT("AggroTarget")));

	if (Target->IsValidLowLevelFast() && GetOwner()->IsValidLowLevelFast()) {

		auto CaculatedSpawnPoint = GetOwner()->GetActorLocation() + ProjectileRelativeSpawnPoint;

		auto Local_Bullet = (ABulletBase*)GetWorld()->SpawnActor(ProjectileClass.Get(), &CaculatedSpawnPoint);

		Local_Bullet->Initialize(Target, ((ATDUnit*)GetOwner())->AttackDamage, ProjectileisDirectable, AffectRange);

	}
}

inline void UProjectileWeaponComponent::InitializeRangedComp(const float inRange=0, const FVector inVector=FVector(0,0,0), UClass * inClass=nullptr, bool inDirectable=false)
{
	InitializeAttackComp(inRange);

	ProjectileRelativeSpawnPoint = inVector;
	ProjectileClass = inClass;
	ProjectileisDirectable = inDirectable;
}

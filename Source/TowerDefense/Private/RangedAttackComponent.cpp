// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedAttackComponent.h"
#include "BulletBase.h"
//#include "Engine\World.h"
//#include "TDUnit.h"
#include "TDCharacter.h"
//#include "Tower.h"

URangedAttackComponent::URangedAttackComponent()
{
	ProjectileRelativeSpawnPoint=FVector(0,0,0);
	ProjectileisDirectable=false;
}


void URangedAttackComponent::ExecAttack(UObject * Target)
{
	if (Target->IsValidLowLevelFast() && GetOwner()->IsValidLowLevelFast()) {

		auto CaculatedSpawnPoint=GetOwner()->GetActorLocation()+ProjectileRelativeSpawnPoint;

		auto Local_Bullet = (ABulletBase*)GetWorld()->SpawnActor(ProjectileClass.Get(), &CaculatedSpawnPoint);

		Local_Bullet->Initialize((ATDCharacter*)Target, ((ATDUnit*)GetOwner())->AttackDamage, ProjectileisDirectable, SplashRange);

	}
}

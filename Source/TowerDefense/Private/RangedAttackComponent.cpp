// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedAttackComponent.h"
#include "BulletBase.h"
//#include "Engine\World.h"
#include "TDUnit.h"
#include "Tower.h"
void URangedAttackComponent::ExecAttack(UObject * Target)
{
	if (Target->IsValidLowLevelFast() && GetOwner()->IsValidLowLevelFast()) {

		auto CaculatedSpawnPoint=GetOwner()->GetActorLocation()+ProjectileRelativeSpawnPoint;

		auto Local_Bullet = (ABulletBase*)GetWorld()->SpawnActor(ProjectileClass.Get(), &CaculatedSpawnPoint);

		if(Cast<ATDUnit>(GetOwner())){
			Local_Bullet-> Initialize((ATDUnit*)Target, ((ATDUnit*)GetOwner())->UnitAttackDamage, ProjectileisDirectable);
		}

		else if (Cast<ATower>(GetOwner())) {
			Local_Bullet->Initialize((ATDUnit*)Target, ((ATower*)GetOwner())->GetTowerAttackDmg(), ProjectileisDirectable);
		}
	}
}

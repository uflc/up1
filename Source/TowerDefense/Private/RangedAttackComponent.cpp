// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedAttackComponent.h"
#include "BulletBase.h"
#include "TDCharacter.h"


void URangedAttackComponent::ExecAttack(UObject * Target)
{
	if (Target->IsValidLowLevelFast() && GetOwner()->IsValidLowLevelFast()) {

		FVector CaculatedSpawnPoint=GetOwner()->GetActorLocation()+ProjectileRelativeSpawnPoint;

		ABulletBase* Local_Bullet = (ABulletBase*)GetWorld()->SpawnActor(ProjectileClass.Get(), &CaculatedSpawnPoint);

		Local_Bullet->Initialize((ATDCharacter*)Target, ((ATDUnit*)GetOwner())->AttackDamage, ProjectileisDirectable);
		
		/*if(Cast<ATDCharacter>(GetOwner())){
			Local_Bullet-> Initialize((ATDCharacter*)Target, ((ATDCharacter*)GetOwner())->AttackDamage, ProjectileisDirectable);
		}

		else if (Cast<ATower>(GetOwner())) {
			Local_Bullet->Initialize((ATDCharacter*)Target, ((ATower*)GetOwner())->AttackDamage, ProjectileisDirectable);
		}*/
	}
}

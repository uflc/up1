// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedAttackComponent.h"
#include "BulletBase.h"
//#include "Engine\World.h"
//#include "TDUnit.h"
#include "TDCharacter.h"
//#include "Tower.h"
#include "AIController.h"
#include "AIModule\Classes\BehaviorTree\BlackboardComponent.h"

URangedAttackComponent::URangedAttackComponent():ProjectileRelativeSpawnPoint(FVector(0,0,0)), ProjectileisDirectable(false)
{
}


void URangedAttackComponent::ExecAttack(ATDCharacter* Target)
{
	if (Target->IsValidLowLevelFast() && GetOwner()->IsValidLowLevelFast()) {

		auto CaculatedSpawnPoint=GetOwner()->GetActorLocation()+ProjectileRelativeSpawnPoint;

		auto Local_Bullet = (ABulletBase*)GetWorld()->SpawnActor(ProjectileClass.Get(), &CaculatedSpawnPoint);

		Local_Bullet->Initialize(Target, ((ATDUnit*)GetOwner())->AttackDamage, ProjectileisDirectable, SplashRange);

	}
}

void URangedAttackComponent::Work()
{
	ATDCharacter* Target = (ATDCharacter*)((AAIController*)((ATDUnit*)GetOwner())->GetController())->GetBlackboardComponent()->GetValueAsObject(FName(TEXT("AggroTarget")));

	if (Target->IsValidLowLevelFast() && GetOwner()->IsValidLowLevelFast()) {

		auto CaculatedSpawnPoint = GetOwner()->GetActorLocation() + ProjectileRelativeSpawnPoint;

		auto Local_Bullet = (ABulletBase*)GetWorld()->SpawnActor(ProjectileClass.Get(), &CaculatedSpawnPoint);

		Local_Bullet->Initialize(Target, ((ATDUnit*)GetOwner())->AttackDamage, ProjectileisDirectable, SplashRange);

	}
}



inline void URangedAttackComponent::Initialize() {
	Super::Initialize();
	ProjectileClass = nullptr;
}

inline void URangedAttackComponent::Initialize(const FVector inVector, UClass * inClass, bool inDirectable) {
	Super::Initialize();
	ProjectileRelativeSpawnPoint = inVector;
	ProjectileClass = inClass;
	ProjectileisDirectable = inDirectable;
}

inline void URangedAttackComponent::Initialize(const float inRange, const FVector inVector, UClass * inClass, bool inDirectable)
{
	URangedAttackComponent::Initialize(inVector, inClass, inDirectable);
	SplashRange=inRange;
}

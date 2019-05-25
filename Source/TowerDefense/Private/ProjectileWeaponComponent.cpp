// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeaponComponent.h"

#include "ProjectileBase.h"

#include "TDCharacter.h"
#include "EffectorComponent.h"
#include "TDWeaponCommonData.h"
#include "TDProjectileCommonData.h"
//#include "Tower.h"
#include "AIController.h"
#include "AIModule\Classes\BehaviorTree\BlackboardComponent.h"

UProjectileWeaponComponent::UProjectileWeaponComponent():ProjectileRelativeSpawnPoint(FVector(0,0,0)), ProjectileisDirectable(false)
{

}

void UProjectileWeaponComponent::BeginPlay(){
}
void UProjectileWeaponComponent::UseWeapon()
{
	if(TargetValidCheck())
	{
		auto Data = WeaponCommon->ProjectileData;

		if(!Data->IsValidLowLevelFast())return; 

		if (!Data->ProjectileClass.Get()->IsValidLowLevelFast())return;

		auto CaculatedSpawnPoint = GetOwner()->GetActorLocation() + ProjectileRelativeSpawnPoint;

		auto Local_Bullet = (AProjectileBase*)GetWorld()->SpawnActor(Data->ProjectileClass.Get(), &CaculatedSpawnPoint);

		auto Effectors = GetSubComponentsByClass(UEffectorComponent::StaticClass());
		for (auto Effector : Effectors) // here
		{
			auto CopyEffector = NewObject<UTDComponent>(Local_Bullet, Effector->StaticClass());
			Local_Bullet->AddOwnedComponent(CopyEffector);
		}

		Local_Bullet->SetCommonData(Data);
		Local_Bullet->SetTarget(vTarget);
		Local_Bullet->Initialize();

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("Use Weapon Done"));
	}
}

//void UProjectileWeaponComponent::InitializeWeaponComp()
//{
//	Super::InitializeWeaponComp();
//
//	// Additional Work
//}

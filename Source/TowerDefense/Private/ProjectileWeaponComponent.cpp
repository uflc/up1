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
		for (auto Effector : Effectors) // ��������
		{
			
			UEffectorComponent*  CopyEffector = DuplicateObject<UEffectorComponent>((UEffectorComponent*)Effector, Local_Bullet);
			//NewObject<UTDComponent>(Local_Bullet, Effector->StaticClass());
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Effector->StaticClass()->GetName());
			UE_LOG(LogTemp, Warning, TEXT("%s"), *CopyEffector->StaticClass()->GetName());
			Local_Bullet->AddOwnedComponent(/*(UEffectorComponent*)*/CopyEffector);
		}

		Local_Bullet->SetCommonData(Data);
		Local_Bullet->SetTarget(vTarget);
		Local_Bullet->Initialize();

	}
}

//void UProjectileWeaponComponent::InitializeWeaponComp()
//{
//	Super::InitializeWeaponComp();
//
//	// Additional Work
//}

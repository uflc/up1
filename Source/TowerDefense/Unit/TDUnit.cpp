// Fill out your copyright notice in the Description page of Project Settings.

#include "TDUnit.h"
#include "TDUnitCommonData.h"
#include "PaperFlipbook.h" //anim
#include "PaperFlipbookComponent.h" //anim
#include "PaperSpriteComponent.h" //shadow
#include "WeaponComponent.h"
#include "TDWeaponCommonData.h"
#include "TowerDefense.h"

ATDUnit::ATDUnit()
{
	//TODO Data as Subobject?
	//UnitData = CreateDefaultSubobject<UTDUnitCommonData>(TEXT("UnitData0"));
	
	Animation = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook0"));
	Animation->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.f));
	Animation->SetWorldLocation(FVector::ZeroVector);
	
	RootComponent = Animation;

	Shadow = CreateOptionalDefaultSubobject<UPaperSpriteComponent>(TEXT("Shadow0"));

	if (Shadow)
	{
		Shadow->SetupAttachment(Animation);
	}
	
	//AttackComp = CreateDefaultSubobject<UMeleeAttackComponent>("AttackComponent");
	//AddOwnedComponent(AttackComp);
}

void ATDUnit::BeginPlay()
{
	Super::BeginPlay();

	CreateUniqueWeapon();
}

void ATDUnit::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	////Test
	//if (UnitData->IsDefaultSubobject())
	//{
	//	TD_LOG(Warning, TEXT("%s is DefSubObj"), *UnitData->GetName());
	//}

}

void ATDUnit::CreateUniqueWeapon()
{
	if (!UnitData)
	{
		TD_LOG(Warning, TEXT("No UnitData!"));
		return;
	}

	TSubclassOf<UWeaponComponent> NewWeaponClass = UnitData->GetWeaponClass();
	if (NewWeaponClass && (!AttackComp || NewWeaponClass != AttackComp->GetClass()))
	{
		AttackComp = NewObject<UWeaponComponent>(this, NewWeaponClass);
	}
	if (!AttackComp)
	{
		TD_LOG(Warning, TEXT("%s: No AttackComp!"), *GetClass()->GetName());
		return;
	}
	
	UTDWeaponCommonData* NewWeaponData = UnitData->GetWeaponData();
	if (!NewWeaponData)
	{
		TD_LOG(Warning, TEXT("%s: No WeaponData!"), *GetClass()->GetName());
		return;
	}
	AttackComp->SetCommonData(NewWeaponData);
}

UPaperFlipbook * ATDUnit::GetDesiredAnimation()
{
	return UnitData ? UnitData->GetAnimations()[(uint8)UnitState].Get() : nullptr;
}

bool ATDUnit::UpdateAnimation()
{
	UPaperFlipbook* DesiredAnim = GetDesiredAnimation();

	if (DesiredAnim)
	{
		Animation->SetFlipbook(DesiredAnim);
		Animation->PlayFromStart();

		if (UnitState == EUnitState::Attacking)
		{
			Animation->SetLooping(false);

		}
		else
		{
			Animation->SetLooping(true);
		}

		return true;
	}
	
	return false;
}

void ATDUnit::ChangeState(EUnitState InState)
{
	UnitState = InState;
	UpdateAnimation();
}

void ATDUnit::UpdateDirection()
{

}

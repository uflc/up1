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

	// Create AttackComponent(Weapon) if not already have one.
	TSubclassOf<UWeaponComponent> WeaponClass = UnitData->GetWeaponClass();
	if (WeaponClass && !AttackComp->IsValidLowLevelFast()) 
	{
		AttackComp = NewObject<UWeaponComponent>(this, WeaponClass);
	}
	//AddOwnedComponent(AttackComp);
	if (!AttackComp)
	{
		//TD_LOG(Warning, TEXT("%s: AttackComp is not valid!"), *GetClass()->GetName());
		return;
	}

	AttackComp->SetCommonData(UnitData->GetWeaponData());
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

bool ATDUnit::IsTargetable()
{
	if (UnitState==EUnitState::Dying || UnitState == EUnitState::Dead) return false;

	return true;
}


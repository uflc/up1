// Fill out your copyright notice in the Description page of Project Settings.

#include "TDUnit.h"
#include "TDUnitCommonData.h"
#include "PaperFlipbook.h" //anim
#include "PaperFlipbookComponent.h" //anim
#include "PaperSpriteComponent.h" //shadow
#include "DirectWeaponComponent.h"


ATDUnit::ATDUnit()
{
	Shadow = CreateOptionalDefaultSubobject<UPaperSpriteComponent>("Shadow");
	Shadow->SetupAttachment(GetRootComponent());

	//AttackComp = CreateDefaultSubobject<UMeleeAttackComponent>("AttackComponent");
	//AddOwnedComponent(AttackComp);
}

void ATDUnit::BeginPlay()
{
	Super::BeginPlay();

	if(!(AttackCompClass.Get())) return;
	AttackComp = NewObject<UWeaponComponent>(this, AttackCompClass.Get());
	AddOwnedComponent(AttackComp);

	InitializeTDComponents();
}

UPaperFlipbook * ATDUnit::GetDesiredAnimation()
{
	return Common->FlipbookMap.Find(UnitState)->Get();
}

bool ATDUnit::UpdateAnimation()
{
	UPaperFlipbook* DesiredAnim = GetDesiredAnimation();

	if (DesiredAnim)
	{
		GetSprite()->SetFlipbook(DesiredAnim);
		return true;
	}
	else return false;

}

void ATDUnit::ChangeState(EUnitState InState)
{
	UnitState = InState;
	UpdateAnimation();
}

void ATDUnit::UpdateDirection()
{
}
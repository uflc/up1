// Fill out your copyright notice in the Description page of Project Settings.

#include "TDUnit.h"
#include "TDUnitCommonData.h"
#include "PaperFlipbook.h" //anim
#include "PaperFlipbookComponent.h" //anim
#include "PaperSpriteComponent.h" //shadow
#include "WeaponComponent.h"
#include "TDWeaponCommonData.h"
#include "Components/BoxComponent.h"
#include "TowerDefense.h"

ATDUnit::ATDUnit()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box0"));
	RootComponent = Box;

	Animation = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook0"));
	Animation->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));

	Shadow = CreateOptionalDefaultSubobject<UPaperSpriteComponent>(TEXT("Shadow0"));
	if (Shadow)
	{
		static const FName ShadowCollisionProfileName(TEXT("NoCollision"));
		Shadow->SetCollisionProfileName(ShadowCollisionProfileName);
		Shadow->SetupAttachment(Animation);
	}
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ATDUnit::BeginPlay()
{
	Super::BeginPlay();

	CreateUniqueWeapon();
}

void ATDUnit::PostInitializeComponents()
{
	Super::PostInitializeComponents();
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

	//////There IS an AttackComp.//////

	AttackComp->SetCommonData(NewWeaponData);
	OnWeaponChanged.Broadcast();
}

UPaperFlipbook* ATDUnit::GetDesiredAnimation_Implementation()
{
	return UnitData ? UnitData->GetAnimations()[(uint8)UnitState].Get() : nullptr;
}

void ATDUnit::UpdateAnimation()
{
	if (!Animation) return;

	UPaperFlipbook* OldAnim = Animation->GetFlipbook();
	UPaperFlipbook* DesiredAnim = GetDesiredAnimation();

	if (DesiredAnim && DesiredAnim != OldAnim)
	{
		if (UnitState == EUnitState::Attacking)
		{
			Animation->SetLooping(false);
		}
		else
		{
			Animation->SetLooping(true);
		}

		Animation->SetFlipbook(DesiredAnim);
	}
}

void ATDUnit::ChangeState(EUnitState InState)
{
	if (InState == UnitState) return;

	UnitState = InState;
	UpdateAnimation();
}

float ATDUnit::GetAggroRange() const
{
	//By default we use attack range as aggro range.
	return	GetAttackRange();
}

float ATDUnit::GetAttackRange() const
{
	return AttackComp ? AttackComp->GetRange() : 0.0f;
}

int32 ATDUnit::GetAttackDamage() const
{
	return AttackComp ? AttackComp->GetDamage() : 0;
}

float ATDUnit::GetAttackSpeed() const
{
	return AttackComp ? AttackComp->GetCooldown() : 0.0f;
}

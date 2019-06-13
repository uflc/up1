// Fill out your copyright notice in the Description page of Project Settings.

#include "TDUnit.h"
#include "TDUnitCommonData.h"
#include "PaperFlipbook.h" //anim
#include "PaperFlipbookComponent.h"
#include "Components/TDPaperFlipbookComponent.h" //anim
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
	Animation->SetupAttachment(Box);

	AnimComp = CreateDefaultSubobject<UTDPaperFlipbookComponent>(TEXT("Anim0"));
	AnimComp->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	AnimComp->SetupAttachment(Box);

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
}

void ATDUnit::SetFlipbooks()
{
	AnimComp->SetFlipbooks(UnitData->GetRealAnimations());
}

void ATDUnit::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(UnitData);

	if (UnitData->IsInitialzied())
	{
		SetFlipbooks();
	}
	else
	{
		UnitData->OnFlipbooksLoaded.AddUObject(this, &ATDUnit::SetFlipbooks);
	}

	CreateUniqueWeapon();
}

void ATDUnit::CreateUniqueWeapon()
{
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
		Animation->SetFlipbook(DesiredAnim);

		if (UnitState == EUnitState::Attacking)
		{
			Animation->SetLooping(false);
			return;
		}
		else
		{
			Animation->SetLooping(true);
		}

		Animation->PlayFromStart();
	}
}

void ATDUnit::ChangeState(EUnitState InState)
{
	if (InState == UnitState) return;

	UnitState = InState;
	AnimComp->ChangeState(InState);
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

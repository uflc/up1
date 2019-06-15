// Fill out your copyright notice in the Description page of Project Settings.

#include "TDUnit.h"
#include "TDUnitCommonData.h"
#include "Components/BoxComponent.h"
#include "Components/DirTDPaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "PaperSpriteComponent.h"
#include "WeaponComponent.h"
#include "TDWeaponCommonData.h"
#include "TowerDefense.h"

FName ATDUnit::AnimationComponentName(TEXT("Flipbook0"));

ATDUnit::ATDUnit()
{
	InitializeDefaults();
}

ATDUnit::ATDUnit(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	InitializeDefaults();
}

void ATDUnit::InitializeDefaults()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box0"));
	RootComponent = Box;

	Animation = CreateAbstractDefaultSubobject<UTDPaperFlipbookComponent>(AnimationComponentName);
	Animation->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	Animation->SetupAttachment(Box);

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

	ApplyData();
}

void ATDUnit::ApplyData()
{
	check(UnitData);

	if (UnitData->IsInitialzied())
	{
		SetFlipbooks();
	}
	else
	{
		UnitData->OnLoadCompleted.AddUObject(this, &ATDUnit::SetFlipbooks);
	}

	CreateUniqueWeapon();
}

void ATDUnit::SetFlipbooks()
{
	Animation->SetFlipbooks(UnitData->GetRealAnimations());
}

void ATDUnit::CreateUniqueWeapon()
{
	check(UnitData);

	TSubclassOf<UWeaponComponent> NewWeaponClass = UnitData->GetWeaponClass();
	if (NewWeaponClass && (!AttackComp || NewWeaponClass != AttackComp->GetClass()))
	{
		AttackComp = NewObject<UWeaponComponent>(this, NewWeaponClass);
	}
	if (!AttackComp)
	{
		//TD_LOG(Warning, TEXT("%s: No AttackComp!"), *GetClass()->GetName());
		return;
	}
	
	UTDWeaponCommonData* NewWeaponData = UnitData->GetWeaponData();
	if (!NewWeaponData)
	{
		TD_LOG(Warning, TEXT("%s: No WeaponData!"), *GetClass()->GetName());
		return;
	}

	//////There are AttackComp and Data.//////

	AttackComp->SetCommonData(NewWeaponData);
	OnWeaponChanged.Broadcast();
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

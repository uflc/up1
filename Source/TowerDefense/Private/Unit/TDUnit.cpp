// Fill out your copyright notice in the Description page of Project Settings.

#include "TDUnit.h"
#include "TDUnitCommonData.h"
#include "Components/DirTDPaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "PaperSpriteComponent.h"
#include "WeaponComponent.h"
#include "TDWeaponCommonData.h"

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
		Shadow->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Shadow->SetCanEverAffectNavigation(false);
		Shadow->SetupAttachment(Animation);
	}

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
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

	CreateUniqueWeapon();
	CreateSkills();

	if (UnitData->IsInitialzied())
	{
		SetFlipbooks();
	}
	else
	{
		UnitData->OnLoadCompleted.AddUObject(this, &ATDUnit::SetFlipbooks);
	}
}

void ATDUnit::SetFlipbooks()
{
	Animation->SetFlipbooks(UnitData->GetRealAnimations());
}

void ATDUnit::CreateUniqueWeapon()
{
	check(UnitData);

	TSubclassOf<UWeaponComponent> NewWeaponClass = UnitData->GetWeaponClass();
	if (NewWeaponClass && (!WeaponComp || NewWeaponClass != WeaponComp->GetClass()))
	{
		WeaponComp = NewObject<UWeaponComponent>(this, NewWeaponClass);
	}
	if (!WeaponComp)
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

	WeaponComp->SetCommonData(NewWeaponData);
	OnWeaponChanged.Broadcast();
}

//This method will clean up old skills
void ATDUnit::CreateSkills()
{
	check(UnitData);

	TArray<TSubclassOf<UWeaponComponent>> NewSkillClassArr = UnitData->GetSkillClassArr();

	if (NewSkillClassArr.Num()!=0 )
	{
		SkillCompArr.Empty();
		
		for (auto NewSkillClass : NewSkillClassArr)
		{
			SkillCompArr.Add(NewObject<UWeaponComponent>(this, NewSkillClass));
		}
	}

	TArray<UTDWeaponCommonData*> NewSkillDataArr= UnitData->GetSkillDataArr();
	if (NewSkillDataArr.Num()==0)
	{
		TD_LOG(Warning, TEXT("%s: No WeaponData!"), *GetClass()->GetName());
		return;
	}

	for( int idx = 0; idx < NewSkillDataArr.Num(); idx++)
	{
		SkillCompArr[idx]->SetCommonData(NewSkillDataArr[idx]);
	}
	//OnSkillsChanged.Broadcast();
}

float ATDUnit::GetAggroRange() const
{
	return	GetAttackRange();
}

float ATDUnit::GetAttackRange() const
{
	return WeaponComp ? WeaponComp->GetRange() : 0.0f;
}

int32 ATDUnit::GetAttackDamage() const
{
	return WeaponComp ? WeaponComp->GetDamage() : 0;
}

float ATDUnit::GetAttackSpeed() const
{
	return WeaponComp ? WeaponComp->GetCooldown() : 0.0f;
}

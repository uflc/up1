// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "TDProjectileCommonData.h"
#include "TDWeaponCommonData.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "EffectorComponent.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Animation = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook Animation"));
	Animation->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	static FName TDProjCollisionProfileName(TEXT("TDProjectile"));
	Animation->SetCollisionProfileName(TDProjCollisionProfileName);
	RootComponent = Animation;

	Effector = CreateDefaultSubobject<UEffectorComponent>(TEXT("Effector0"));
}

void AProjectileBase::SetCommonData(UTDProjectileCommonData* InData, FEffectorData EffectorData, bool bShouldTick)
{ 
	if (!InData || ProjectileCommon == InData) return;

	ProjectileCommon = InData;

	Effector->Initialize(EffectorData.DefaultSplashRange, EffectorData.DefaultDamage, EffectorData.DebuffArray);

	//
	const TSoftObjectPtr<UPaperFlipbook>* FlipbookSoftPtr = ProjectileCommon->GetFlipbookMap().Find(EWeaponFlipbookType::Projectile);
	if (!FlipbookSoftPtr) return;
	UPaperFlipbook* Flipbook = FlipbookSoftPtr->Get();
	if (!Flipbook) return;

	Animation->SetFlipbook(Flipbook);

	if (bShouldTick)
	{
		SetActorTickEnabled(true);
	}
}

void AProjectileBase::BulletDestroy()
{
	//
	const TSoftObjectPtr<UPaperFlipbook>* FlipbookSoftPtr = ProjectileCommon->GetFlipbookMap().Find(EWeaponFlipbookType::Effect);
	if (FlipbookSoftPtr)
	{
		UPaperFlipbook* Flipbook = FlipbookSoftPtr->Get();
		if (Flipbook)
		{
			Animation->SetFlipbook(Flipbook);
			Animation->SetLooping(false);
		}
	}
	const static float ProjectileRemainingTime = 0.5f;
	SetLifeSpan(ProjectileRemainingTime);
}

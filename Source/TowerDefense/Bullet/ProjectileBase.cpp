// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "TDProjectileCommonData.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "EffectorComponent.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Animation = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook Animation"));
	Animation->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	static FName TDProjCollisionProfileName(TEXT("TDProjectile"));
	Animation->SetCollisionProfileName(TDProjCollisionProfileName);
	RootComponent = Animation;

	Effector = CreateDefaultSubobject<UEffectorComponent>(TEXT("Effector0"));
}


void AProjectileBase::SetCommonData(UTDProjectileCommonData* InData) 
{ 
	ProjectileCommon = InData; 

	if (!ProjectileCommon) return;

	Speed         = ProjectileCommon->Velocity;
	bIsDirectable = ProjectileCommon->bIsDirectable;

	//
	UPaperFlipbook* Flipbook = ProjectileCommon->FlipbookMap.Find(EWeaponFlipbookType::Projectile)->Get();
	if (!Flipbook) return;

	Animation->SetFlipbook(Flipbook);
}

//임시 데이터 전달
void AProjectileBase::SetEffector(float EffectRange, uint32 Damage)
{
	Effector->Initialize(EffectRange, Damage);
}

void AProjectileBase::SetEffector(const TArray<FDebuff>& InDebuffArray)
{
	Effector->Initialize(InDebuffArray);
}

void AProjectileBase::BulletDestroy()
{
	//
	TSoftObjectPtr<UPaperFlipbook>* FlipbookSoftPtr = ProjectileCommon->FlipbookMap.Find(EWeaponFlipbookType::Effect);

	if (FlipbookSoftPtr == nullptr) 
	{
		Destroy(); 
		return;
	}

	Animation->SetFlipbook(FlipbookSoftPtr->Get());
	Animation->SetLooping(false);
	SetLifeSpan(Animation->GetFlipbookLength());
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "TDProjectileCommonData.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "EffectorComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Animation = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook Animation"));
	Animation->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.f));

	RootComponent = Animation;

	Effector = CreateDefaultSubobject<UEffectorComponent>(TEXT("Effector0"));
}


void AProjectileBase::SetCommonData(UTDProjectileCommonData* InData) 
{ 
	ProjectileCommon = InData; 

	if (!ProjectileCommon) return;

	Velocity	  = ProjectileCommon->Velocity;
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

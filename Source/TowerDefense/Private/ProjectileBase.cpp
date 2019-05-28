// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "TDProjectileCommonData.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Animation = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook Animation"));
	Animation->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.f));

	RootComponent = Animation;
}

FORCEINLINE void AProjectileBase::SetTarget(ATDCharacter * InTarget) { Target = InTarget; }

FORCEINLINE void AProjectileBase::SetCommonData(UTDProjectileCommonData* InData) { ProjectileCommon = InData; }

void AProjectileBase::Initialize()
{
	UTDProjectileCommonData* Data = ProjectileCommon;

	Velocity = Data->Velocity;
	IsDirectable = Data->Directable;

	TSoftObjectPtr<UPaperFlipbook>* FlipbookSoftPtr =  Data->FlipbookMap.Find(EWeaponFlipbookType::Projectile);
	if (FlipbookSoftPtr == nullptr) return;

	Animation->SetFlipbook(FlipbookSoftPtr->Get());
}

void AProjectileBase::BulletDestroy()
{
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

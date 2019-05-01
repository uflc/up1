// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBase.h"

// Sets default values
ABulletBase::ABulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABulletBase::Tick(float DeltaTime)
{
	if (!Target) {
		BulletDestroy();
		return;
	}

	auto DirectionVec = Target->GetActorLocation() - GetActorLocation();
	DirectionVec.Z = 0;

	float DirectionVecSize = DirectionVec.Size();
	if (DirectionVecSize <= 40.0f) {
		Target->ApplyDamage(8.0f, 0.15f, Damage);
		SetActorTickEnabled(false);
		BulletDestroy();
		return;
	}

	DirectionVec.Normalize();
	DirectionVec *= (Velocity * DeltaTime);

	SetActorLocation(GetActorLocation() + DirectionVec);
	if(IsDirectable){ 
		DirectionVec.Rotation();
		SetActorRotation(FRotator(0, DirectionVec.Rotation().Yaw,0));
	}
}

void ABulletBase::Initialize(AMyPaperCharacter * iTarget, int32 iDamage,bool iIsDirectable = false)
{
	Target = iTarget;
	Damage = iDamage;
	IsDirectable=iIsDirectable;
}

void ABulletBase::BulletDestroy_Implementation()
{
	Destroy();
}
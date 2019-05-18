// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBase.h"
#include "TDCharacter.h"

FVector ABulletBase::GetDistanceVecToTarget()
{
	return Target->GetActorLocation() - GetActorLocation();
}

void ABulletBase::CalcVelocityVec(const FVector& DirectionVec)
{
	VelocityVec = DirectionVec * Velocity;
}

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
		SetActorTickEnabled(false);
		BulletDestroy();
		return;
	}

	FVector DistanceVec = GetDistanceVecToTarget();
	DistanceVec.Z = 0;
	float Distance = DistanceVec.Size();

	if (Distance <= 40.0f)
	{
		Target->TDUnitTakeDamage(8.0f, 0.15f, Damage);
		SetActorTickEnabled(false);
		BulletDestroy();
		return;
	}

	DistanceVec.Normalize();
	CalcVelocityVec(DistanceVec);
//
//	DirectionVec *= (Velocity * DeltaTime);

	SetActorLocation(GetActorLocation() + VelocityVec * DeltaTime);
	if (IsDirectable)	SetActorRotation(FRotator(0, (VelocityVec/** DeltaTime*/*-1).Rotation().Yaw,0));
}

void ABulletBase::Initialize(ATDCharacter * iTarget, int32 iDamage,bool iIsDirectable = false)
{
	Target = iTarget;
	Damage = iDamage;
	IsDirectable=iIsDirectable;
}

void ABulletBase::BulletDestroy_Implementation()
{
	Destroy();
}
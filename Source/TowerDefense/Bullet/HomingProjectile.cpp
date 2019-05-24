// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingProjectile.h"
#include "EffectorComponent.h"
#include "TDCharacter.h"

FVector AHomingProjectile::GetDistanceVecToTarget()
{
	return Target->GetActorLocation() - GetActorLocation();
}

void AHomingProjectile::CalcVelocityVec(const FVector& DirectionVec)
{
	VelocityVec = DirectionVec * Velocity;
}

// Sets default values
AHomingProjectile::AHomingProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AHomingProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHomingProjectile::Tick(float DeltaTime)
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
		//Target->TDUnitTakeDamage(8.0f, 0.15f, Damage);
		auto Effectors = GetComponentsByClass(UEffectorComponent::StaticClass());
		for (auto Effector : Effectors)
		{
			((UEffectorComponent*)Effector)->AffectTarget(Target);
		}

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

void AHomingProjectile::Initialize(ATDCharacter * iTarget, int32 iDamage,bool iIsDirectable = false, float iSplashRange=0)
{
	Target = iTarget;
	Damage = iDamage;
	IsDirectable=iIsDirectable;
	SplashRange= iSplashRange;
}

void AHomingProjectile::BulletDestroy_Implementation()
{
	Destroy();
}
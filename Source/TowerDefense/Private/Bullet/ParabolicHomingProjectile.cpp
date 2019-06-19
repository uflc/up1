// Fill out your copyright notice in the Description page of Project Settings.


#include "ParabolicHomingProjectile.h"
#include "TDProjectileCommonData.h"

void AParabolicHomingProjectile::CalcVelocityVec(const FVector& DirectionVec)
{
	Super::CalcVelocityVec(DirectionVec);
	VelocityVec = (DefVelocityVec * (1 - TickCounter)) + (VelocityVec * TickCounter);
}

void AParabolicHomingProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickCounter += (DeltaTime / (DefVecSize * 0.4f));
	if (TickCounter >= 1.0f)
	{
		TickCounter = 1.0f;
	}
}

void AParabolicHomingProjectile::SetCommonData(UTDProjectileCommonData* InData, FEffectorData EffectorData, bool bShouldTick)
{
	if (!InData || ProjectileCommon == InData) return;

	Super::SetCommonData(InData, EffectorData);
	
	CurveScale = 0.72f * 1000.0f / ProjectileCommon->GetVelocity();
	TickCounter = 0.0f;

	DefVelocityVec = GetDistanceVecToTarget();
	DefVelocityVec.Z = 0.0f;

	DefVecSize = DefVelocityVec.Size() / 600.0f >= 1.0f ? 1.0f : DefVelocityVec.Size() / 1000.0f;

	DefVelocityVec.Normalize();
	DefVelocityVec *= ProjectileCommon->GetVelocity();

	DefVelocityVec.Y -= (CurveScale * ProjectileCommon->GetVelocity());

	if (bShouldTick)
	{
		SetActorTickEnabled(true);
	}
}





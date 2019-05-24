// Fill out your copyright notice in the Description page of Project Settings.


#include "ParabolicHomingProjectile.h"

void AParabolicHomingProjectile::CalcVelocityVec(const FVector& DirectionVec)
{
	Super::CalcVelocityVec(DirectionVec);
	VelocityVec = (DefVelocityVec*(1 - TickCounter)) + (VelocityVec * TickCounter);
}

void AParabolicHomingProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TeleportTo(GetActorLocation() + (VelocityVec*DeltaTime),GetActorRotation());

	//DirectionVec.Normalize();
	//DirectionVec *= Velocity;

	//VelocityVec = (DefVelocityVec*(1 - TickCounter)) + (DirectionVec * TickCounter);

	//SetActorLocation(GetActorLocation() + (VelocityVec*DeltaTime)); 
	
	TickCounter += (DeltaTime/(DefVecSize*0.4f));
	if(TickCounter>=1.0f)	TickCounter=1.0f;

	//if (IsDirectable) SetActorRotation(FRotator(0, (VelocityVec*-1).Rotation().Yaw, 0));
}

void AParabolicHomingProjectile::Initialize(ATDCharacter * iTarget, int32 iDamage,bool IisDirectable, float iSplashRange)
{
	Super::Initialize(iTarget, iDamage, IisDirectable, iSplashRange);

	CurveScale = 0.72f*1000.0f/Velocity;
	TickCounter = 0;

	DefVelocityVec = GetDistanceVecToTarget();
	DefVelocityVec.Z = 0;

	DefVecSize = DefVelocityVec.Size()/600.0f >= 1.0f ? 1.0f : DefVelocityVec.Size() / 1000.0f;

	DefVelocityVec.Normalize();
	DefVelocityVec*=Velocity;

	DefVelocityVec.Y-=(CurveScale*Velocity);

}

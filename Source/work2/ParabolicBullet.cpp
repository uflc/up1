// Fill out your copyright notice in the Description page of Project Settings.


#include "ParabolicBullet.h"

void AParabolicBullet::Tick(float DeltaTime)
{
	if (!Target) {
		BulletDestroy();
		return;
	}

	auto DirectionVec = Target->GetActorLocation() - GetActorLocation();
	DirectionVec.Z=0;
	float DirectionVecSize = DirectionVec.Size();
	if(DirectionVecSize <= 40.0f) {
		Target->ApplyDamage(8.0f,0.15f,Damage);
		BulletDestroy();
		return;
	}

	//TeleportTo(GetActorLocation() + (VelocityVec*DeltaTime),GetActorRotation());

	DirectionVec.Normalize();
	DirectionVec *= Velocity;

	VelocityVec = (DefVelocityVec*(1 - TickCounter)) + (DirectionVec * TickCounter);

	SetActorLocation(GetActorLocation() + (VelocityVec*DeltaTime)); 
	
	TickCounter += (DeltaTime/(DefVecSize*0.4f));
	if(TickCounter>=1.0f)	TickCounter=1.0f;

	if (IsDirectable) SetActorRotation(FRotator(0, (VelocityVec*-1).Rotation().Yaw, 0));
}



void AParabolicBullet::Initialize(AMyPaperCharacter * iTarget, int32 iDamage,bool IisDirectable)
{
	Target= iTarget;
	Damage=iDamage;
	IsDirectable= IisDirectable;
	CurveScale=0.72f*1000.0f/Velocity;
	TickCounter=0;

	DefVelocityVec= Target->GetActorLocation() - GetActorLocation();
	DefVelocityVec.Z = 0;

	DefVecSize = DefVelocityVec.Size()/600.0f >= 1.0f ? 1.0f : DefVelocityVec.Size() / 1000.0f;

	DefVelocityVec.Normalize();
	DefVelocityVec*=Velocity;

	DefVelocityVec.Y-=(CurveScale*Velocity);

}

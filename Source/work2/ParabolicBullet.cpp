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

	if( DirectionVec.Size() <= 20.0f) {
		Target->ApplyDamage(8.0f,0.15f,0/*Damage*/);
		BulletDestroy();
		return;
	}

	//TeleportTo(GetActorLocation() + (VelocityVec*DeltaTime),GetActorRotation());
	SetActorLocation(GetActorLocation() + (VelocityVec*DeltaTime)); 
	DirectionVec.Normalize();
	DirectionVec *= Velocity;
	Counter+= DeltaTime*0.4f;
	//Counter = (Counter>=1.0f) ? 1.0 : Counter;
	if (Counter >= 0.125f) {
		Counter =0.125f;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("Counter is MAX"));
	}
	VelocityVec = (VelocityVec*(1- Counter)) + (DirectionVec*Counter);
	
}

void AParabolicBullet::BulletDestroy_Implementation()
{
	Destroy();
}

void AParabolicBullet::Initialize(AMyPaperCharacter * iTarget, int32 iDamage)
{
	Target= iTarget;
	Damage=iDamage;
	StartingVelocityPercent=1.0f;
	CurveScale=0.8f/ StartingVelocityPercent;

	Counter = 0.00f;

	VelocityVec= Target->GetActorLocation() - GetActorLocation();
	VelocityVec.Z = 0;
	VelocityVec.Normalize();
	VelocityVec.Y-=CurveScale;
	VelocityVec.Normalize();
	VelocityVec *= Velocity * StartingVelocityPercent;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "DebuffComponent.h"
#include "TDCharacter.h"
#include "GameFramework\FloatingPawnMovement.h"
#include "TimerManager.h"
#include "Engine\World.h"

void UDebuffComponent::Initialize(const FDebuffSet & InDebuffInfo)
{
	DebuffInfo= InDebuffInfo;

	FTimerHandle Handle;



	ATDCharacter* Target=(ATDCharacter*)GetOwner();
	UFloatingPawnMovement* Movement;
	TArray<UActorComponent*> TDComponentArray;

	if (Target->IsValidLowLevel()&& Target->GetMovementComponent()->IsValidLowLevel())
	{
		Movement = Cast<UFloatingPawnMovement>(Target->GetMovementComponent());
	}
	
	EDebuffType Type=DebuffInfo.Type;


	switch (Type) 
	{
		case EDebuffType::Slow:
			if (Movement)
			{
				Movement->MaxSpeed *= (DebuffInfo.Power / 100.0f);
			}
			break;

		case EDebuffType::Snared:
			if (Movement)
			{
				Movement->MaxSpeed = 0;
			}
			break;

		case EDebuffType::Stun:
			if (Movement)
			{
				Movement->MaxSpeed = 0;
			}

			TDComponentArray = Target->GetComponentsByClass(UTDComponent::StaticClass());

			for(UActorComponent* Comp : TDComponentArray)
			{
				(UTDComponent*)Comp->Deactivate();
			}
			break;

		default:
			return;
	}
	

	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateUObject(this, &UDebuffComponent::DeactivateDebuff), DebuffInfo.Duration, false);
}

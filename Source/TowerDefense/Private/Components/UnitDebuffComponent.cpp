// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitDebuffComponent.h"
#include "TDCharacter.h"
#include "GameFramework\FloatingPawnMovement.h"
#include "WeaponComponent.h"

#include "Engine\World.h"
#include "TimerManager.h"


UUnitDebuffComponent::UUnitDebuffComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FORCEINLINE void UUnitDebuffComponent::RegDebuff(const FDebuff& Debuff)
{
	DebuffMap.Add(Debuff.Type,Debuff);

	UpdateStat(Debuff.Type);

	FTimerHandle Handle;
	FTimerDelegate TimerDel/*=FTimerDelegate::CreateUObject(this,&UUnitDebuffComponent::UnregDebuff,Debuff)*/;
	TimerDel.BindUFunction(this, FName("UnregDebuff"), Debuff);

	GetWorld()->GetTimerManager().SetTimer(Handle, TimerDel, Debuff.Duration, false);

}

FORCEINLINE void UUnitDebuffComponent::UnregDebuff(const FDebuff& Debuff)
{
	DebuffMap.RemoveSingle(Debuff.Type, Debuff);

	UpdateStat(Debuff.Type);
}

void UUnitDebuffComponent::UpdateStat(const EDebuffType& InDebuffType)
{
	const ATDCharacter* Owner = (ATDCharacter*)GetOwner();
	//	const float DefaultSpeed= Owner->Common;
	UFloatingPawnMovement* Movement = (UFloatingPawnMovement*)Owner->GetMovementComponent();
	TArray<UActorComponent*> WeaponArr = Owner->GetComponentsByClass(UWeaponComponent::StaticClass());

	TArray<FDebuff> DebuffArr;
	DebuffMap.MultiFind(InDebuffType, DebuffArr);

	// using this or move to component property
	bool bIsDebuffOn= (DebuffArr.Num()!=0);
	float OverlapPower=0;

	if(InDebuffType ==EDebuffType::Slow)//(bIsOverlap)
	{
		for (auto Debuff : DebuffArr)
		{
			OverlapPower+=Debuff.Power;
		}
		// Movement->MaxSpeed=DefaultSpeed*OverlapPower;
	}
	else 
	{
		switch (InDebuffType)
		{
			case EDebuffType::Snared:
				if (bIsDebuffOn)
				{
					Movement->Deactivate();
				}
				else
				{
					Movement->Activate();
				}
				break;

			case EDebuffType::Stun:
				if (bIsDebuffOn)
				{
					Movement->Deactivate();
					for (auto WeaponComp : WeaponArr)
					{
						WeaponComp->Deactivate();
					}
				}
				else
				{
					Movement->Activate();
					for (auto WeaponComp : WeaponArr)
					{
						WeaponComp->Activate();
					}
				}				
				break;

			default:
				break;
		}
	}
}
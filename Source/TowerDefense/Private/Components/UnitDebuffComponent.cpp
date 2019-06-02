// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitDebuffComponent.h"
#include "TDCharacter.h"
#include "GameFramework\FloatingPawnMovement.h"
#include "WeaponComponent.h"

#include "Engine\World.h"
#include "TimerManager.h"

void UUnitDebuffComponent::RegDebuff(const FDebuff& Debuff)
{
	DebuffMap.Add(Debuff.Type,Debuff);

	UpdateStat(Debuff, true);

	FTimerHandle		Handle;
	FTimerDelegate	TimerDel/*=FTimerDelegate::CreateUObject(this,&UUnitDebuffComponent::UnregDebuff,Debuff)*/;

	TimerDel.BindUFunction(this, FName("UnregDebuff"), Debuff);

	GetWorld()->GetTimerManager().SetTimer(Handle, TimerDel, Debuff.Duration, false);

}

void UUnitDebuffComponent::UnregDebuff(const FDebuff& Debuff)
{
	DebuffMap.RemoveSingle(Debuff.Type, Debuff);

	UpdateStat(Debuff, false);
}

void UUnitDebuffComponent::UpdateStat(const FDebuff& InDebuff, bool bDebuffStart)
{
	static const float StopMovementValue = 0.00001f;

	const			ATDCharacter*			Owner					=		(ATDCharacter*)GetOwner();
	UFloatingPawnMovement*		Movement			=		(UFloatingPawnMovement*)Owner->GetMovementComponent();
	TArray<UActorComponent*>	WeaponArr			=		Owner->GetComponentsByClass(UWeaponComponent::StaticClass());

	TArray<FDebuff>							DebuffArr;


	// Overlappable ( Slow, Exhaust { AttkSpd,MovementSpd }, etc )

	if ( IsDebuffTypeOverlappable(InDebuff.Type) )
	{
		const float PowerToPercent = (1 - (InDebuff.Power / 100));

		switch ( InDebuff.Type )
		{
			case EDebuffType::Slow:
				if ( bDebuffStart )
				{
					Movement->MaxSpeed *= PowerToPercent;
				}
				else
				{
					Movement->MaxSpeed /= PowerToPercent;
				}
				break;

			default:
				break;
		}
	}

	// Not Overlappable ( Stun, Snared, Taunt, Sleep, etc )
	else 
	{
		DebuffMap.MultiFind(InDebuff.Type, DebuffArr);

		bool bIsDebuffRemain = (DebuffArr.Num() != 0);

		switch ( InDebuff.Type )
		{
			case EDebuffType::Snared:
				if ( bIsDebuffRemain )
				{
					//Movement->Deactivate();
					Movement->MaxSpeed *= StopMovementValue;
				}
				else
				{
					//Movement->Activate();
					Movement->MaxSpeed /= StopMovementValue;
				}
				break;

			case EDebuffType::Stun:
				if ( bIsDebuffRemain )
				{
					Movement->MaxSpeed *= StopMovementValue;
					for ( auto WeaponComp : WeaponArr )
					{
						WeaponComp->Deactivate();
					}
				}
				else
				{
					Movement->MaxSpeed /= StopMovementValue;
					for ( auto WeaponComp : WeaponArr )
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

FORCEINLINE bool UUnitDebuffComponent::IsDebuffTypeOverlappable(const EDebuffType & InDebuffType)
{
	bool RetVal;
	switch (InDebuffType)
	{
		case EDebuffType::Slow:
			RetVal = true;
			break;

		case EDebuffType::Snared:
		case EDebuffType::Stun:
		default:
			RetVal = false;
			break;

	}
	return RetVal;
}

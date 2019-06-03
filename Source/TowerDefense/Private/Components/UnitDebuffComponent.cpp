// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitDebuffComponent.h"
#include "TDCharacter.h"
#include "GameFramework\FloatingPawnMovement.h"
#include "WeaponComponent.h"

#include "Engine\World.h"
#include "TimerManager.h"

void UUnitDebuffComponent::RegDebuff(const FDebuff& Debuff)
{
	const bool bIsDuplicated = TimerMap.Contains(Debuff.ID);

	FTimerHandle*		Handle;
	FTimerDelegate	TimerDel;

	TimerDel.BindUFunction(this, FName("UnregDebuff"), Debuff);

	// I don't know why but cannot do this
	//FTimerDelegate TimerDel = FTimerDelegate::CreateUObject(this,&UUnitDebuffComponent::UnregDebuff,Debuff);

	if ( bIsDuplicated )
	{
		UpdateStat(Debuff, false);

		FDebuff* RegisteredDebuff = DebuffMap.FindPair(Debuff.Type, Debuff);

		Handle = TimerMap.Find(Debuff.ID);

		GetWorld()->GetTimerManager().ClearTimer(*Handle);
	
		// Replace old timer
		TimerMap.Remove(Debuff.ID);

		TimerMap.Add(Debuff.ID, FTimerHandle());
		
		if ( Debuff.MaxStack > RegisteredDebuff->CurrentStack )
		{
			// Debuff.CurrentStack is Additional Stack. Set this when intialize debuff info
			RegisteredDebuff->CurrentStack += Debuff.CurrentStack;

			// Decrease to MaxStack 
			RegisteredDebuff->CurrentStack = Debuff.MaxStack <= RegisteredDebuff->CurrentStack ? Debuff.MaxStack : RegisteredDebuff->CurrentStack ;
		}
	}

	else 
	{
		TimerMap.Add(Debuff.ID, FTimerHandle());

		DebuffMap.Add(Debuff.Type, Debuff);
	}

	Handle = TimerMap.Find(Debuff.ID);

	GetWorld()->GetTimerManager().SetTimer(*Handle, TimerDel, Debuff.Duration, false);

	UpdateStat(Debuff, true);

}

void UUnitDebuffComponent::UnregDebuff(FDebuff& Debuff)
{
	TD_LOG(Warning, TEXT("UnReg"));

	if( Debuff.CurrentStack - 1 <= 0 )
	{ 
		DebuffMap.RemoveSingle(Debuff.Type, Debuff);
		TimerMap.Remove(Debuff.ID);
		UpdateStat(Debuff, false);
	}

	else
	{
		UpdateStat(Debuff, false);

		Debuff.CurrentStack--;
		FTimerHandle*		Handle;
		FTimerDelegate	TimerDel;

		Handle = TimerMap.Find(Debuff.ID);

		TimerDel.BindUFunction(this, FName("UnregDebuff"), Debuff);

		GetWorld()->GetTimerManager().SetTimer(*Handle, TimerDel, Debuff.Duration, false);

		UpdateStat(Debuff, true);
	}

	
}

void UUnitDebuffComponent::UpdateStat(const FDebuff& InDebuff, bool bDebuffStart)
{
	static const float StopMovementValue = 0.00001f;

	const			ATDCharacter*			Owner					=		(ATDCharacter*)GetOwner();
	UFloatingPawnMovement*		Movement			=		(UFloatingPawnMovement*)Owner->GetMovementComponent();
	TArray<UActorComponent*>	WeaponArr			=		Owner->GetComponentsByClass(UWeaponComponent::StaticClass());

	TArray<FDebuff>							DebuffArr;

	static float DefaultSpeed = 600.0f; // Owner's default speed
	static float MinSpeed = 50.0f;

	// Overlappable ( Slow, Exhaust { AttkSpd,MovementSpd }, etc )
	if ( IsDebuffTypeOverlappable(InDebuff.Type) )
	{
		const float PowerToPercent = (1 - ( InDebuff.GetCalculatedPower() / 100));

		switch ( InDebuff.Type )
		{
			case EDebuffType::Slow:
				if ( bDebuffStart )
				{
					DefaultSpeed *= PowerToPercent;
					Movement->MaxSpeed = DefaultSpeed >= MinSpeed ? DefaultSpeed : MinSpeed;

					//Movement->MaxSpeed *= PowerToPercent;
				}
				else
				{
					DefaultSpeed /= PowerToPercent;
					Movement->MaxSpeed = DefaultSpeed >= MinSpeed ? DefaultSpeed : MinSpeed;

					//Movement->MaxSpeed /= PowerToPercent;
				}
				break;

			//case EDebuffType::Exhaust:
			//if (bDebuffStart)
			//{
			//	Movement->MaxSpeed *= PowerToPercent;
			//	for ( auto WeaponComp : WeaponArr )
			//		{
			//		WeaponComp->SetDelay();
			//		}
			//}
			//else
			//{
			//	Movement->MaxSpeed /= PowerToPercent;
			//	for ( auto WeaponComp : WeaponArr )
			//		{
			//		WeaponComp->SetDelay();
			//		}
			//}
			//}
			//break;

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

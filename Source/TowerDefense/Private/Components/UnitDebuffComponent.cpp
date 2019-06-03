// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitDebuffComponent.h"
#include "TDCharacter.h"
#include "GameFramework\FloatingPawnMovement.h"
#include "WeaponComponent.h"

#include "Engine\World.h"
#include "TimerManager.h"

void UUnitDebuffComponent::RegDebuff(const FDebuff& InDebuff)
{
	const bool bIsDuplicated = TimerMap.Contains(InDebuff.ID);

	FTimerHandle*		Handle;
	FTimerDelegate	TimerDel;
	
	FDebuff* RegisteredDebuff;

	// I don't know why but cannot do this
	//FTimerDelegate TimerDel = FTimerDelegate::CreateUObject(this,&UUnitDebuffComponent::UnregDebuff,Debuff);

	if ( bIsDuplicated )
	{
		RegisteredDebuff = DebuffMap.FindPair(InDebuff.Type, InDebuff);

		UpdateStat(*RegisteredDebuff, false);

		Handle = TimerMap.Find(InDebuff.ID);

		GetWorld()->GetTimerManager().ClearTimer(*Handle);
	
		// Replace old timer
		TimerMap.Remove(InDebuff.ID);

		TimerMap.Add(InDebuff.ID, FTimerHandle());
		
		if ( InDebuff.MaxStack > RegisteredDebuff->CurrentStack )
		{
			// Debuff.CurrentStack is Additional Stack. Set this when intialize debuff info
			RegisteredDebuff->CurrentStack += InDebuff.CurrentStack;

			// Decrease to MaxStack 
			RegisteredDebuff->CurrentStack = InDebuff.MaxStack <= RegisteredDebuff->CurrentStack ? InDebuff.MaxStack : RegisteredDebuff->CurrentStack ;
		}
	}

	else 
	{
		TimerMap.Add(InDebuff.ID, FTimerHandle());

		//DebuffMap.Add(InDebuff.Type, InDebuff);

		RegisteredDebuff = &DebuffMap.Add(InDebuff.Type, InDebuff); 

		//DebuffMap.FindPair(InDebuff.Type, InDebuff);
	}

	TimerDel.BindUFunction(this, FName("UnregDebuff"), *RegisteredDebuff);

	Handle = TimerMap.Find(InDebuff.ID);

	GetWorld()->GetTimerManager().SetTimer(*Handle, TimerDel, InDebuff.Duration, false);
	
	UpdateStat(*RegisteredDebuff, true);
}

void UUnitDebuffComponent::UnregDebuff(FDebuff& InDebuff)
{
	/*TD_LOG(Warning,TEXT("%d"), InDebuff.CurrentStack);*/

	if( InDebuff.CurrentStack - 1 <= 0 )
	{ 
		DebuffMap.RemoveSingle(InDebuff.Type, InDebuff);
		TimerMap.Remove(InDebuff.ID);
		UpdateStat(InDebuff, false);
	}

	else
	{
		UpdateStat(InDebuff, false);


		InDebuff.CurrentStack--;
		FTimerHandle*		Handle;
		FTimerDelegate	TimerDel;

		Handle = TimerMap.Find(InDebuff.ID);

		TimerDel.BindUFunction(this, FName("UnregDebuff"), InDebuff);

		GetWorld()->GetTimerManager().SetTimer(*Handle, TimerDel, InDebuff.Duration, false);

		UpdateStat(InDebuff, true);
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
		//FDebuff* RegisteredDebuff = DebuffMap.FindPair(InDebuff.Type, InDebuff);

		//if (!RegisteredDebuff) return;

		const float PowerToPercent = (1 - (InDebuff.GetCalculatedPower() / 100));

		switch ( InDebuff.Type )
		{
			case EDebuffType::Slow:
				if ( bDebuffStart )
				{
					//DefaultSpeed *= PowerToPercent;
					//Movement->MaxSpeed = DefaultSpeed >= MinSpeed ? DefaultSpeed : MinSpeed;

					Movement->MaxSpeed *= PowerToPercent;
				}
				else
				{
					//DefaultSpeed /= PowerToPercent;
					//Movement->MaxSpeed = DefaultSpeed >= MinSpeed ? DefaultSpeed : MinSpeed;
					Movement->MaxSpeed /= PowerToPercent;
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

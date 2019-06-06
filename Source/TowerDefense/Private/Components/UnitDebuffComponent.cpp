// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitDebuffComponent.h"
#include "TDCharacter.h"
#include "GameFramework\FloatingPawnMovement.h"
#include "WeaponComponent.h"
#include "TimerManager.h"

void UUnitDebuffComponent::RegDebuff(const FDebuff& InDebuff)
{
	FTimerHandle*   HandlePtr;
	FTimerDelegate  TimerDel;
	
	FDebuff* DebuffPtr;

	const bool bIsStacked = TimerMap.Contains(InDebuff.ID);
	if ( bIsStacked )
	{
		//Find and deactive current stacked debuff cause we re-calculate and re-set it based on new data: especialy, CurrentStack count.
		DebuffPtr = DebuffMap.FindPair(InDebuff.Type, InDebuff);
		UpdateStat(*DebuffPtr, false);
		
		if ( IsDebuffTypeOverlappable(DebuffPtr->Type)&& InDebuff.MaxStack > DebuffPtr->CurrentStack )
		{
			// Debuff.CurrentStack is Additional Stack.
			DebuffPtr->CurrentStack += InDebuff.CurrentStack;

			// Validate Debuff stack count which should not over MaxStack
			DebuffPtr->CurrentStack = InDebuff.MaxStack <= DebuffPtr->CurrentStack ? InDebuff.MaxStack : DebuffPtr->CurrentStack ;
		}
	}
	else 
	{
		//Create new timer for new debuff
		TimerMap.Add(InDebuff.ID, FTimerHandle());
		DebuffPtr = &DebuffMap.Add(InDebuff.Type, InDebuff); 
	}

	//Set debuff duration.
	TimerDel.BindUFunction(this, FName("UnregDebuff"), *DebuffPtr);
	HandlePtr = TimerMap.Find(InDebuff.ID);
	GetWorld()->GetTimerManager().SetTimer(*HandlePtr, TimerDel, InDebuff.Duration, false);
	TD_LOG(Warning, TEXT("SetDebuffTimer"));

	//Apply new data
	UpdateStat(*DebuffPtr, true);
}

void UUnitDebuffComponent::UnregDebuff(FDebuff& InDebuff)
{
	//¼­¼ø
	//UpdateStat(InDebuff, false);

	if ( IsDebuffTypeOverlappable(InDebuff.Type) || InDebuff.CurrentStack-1 <= 0 )
	{ 
		DebuffMap.RemoveSingle(InDebuff.Type, InDebuff);
		TimerMap.Remove(InDebuff.ID);
		UpdateStat(InDebuff, false);
	}
	else
	{
		FTimerHandle*  HandlePtr;
		FTimerDelegate TimerDel;

		UpdateStat(InDebuff, false);

		InDebuff.CurrentStack--;

		HandlePtr = TimerMap.Find(InDebuff.ID);
		TimerDel.BindUFunction(this, FName("UnregDebuff"), InDebuff);
		GetWorld()->GetTimerManager().SetTimer(*HandlePtr, TimerDel, InDebuff.Duration, false);

		UpdateStat(InDebuff, true);
	}
}

void UUnitDebuffComponent::UpdateStat(const FDebuff& InDebuff, bool bDebuffStart)
{
	//CharacterStats
	const ATDCharacter*      Owner     = (ATDCharacter*)GetOwner();
	UFloatingPawnMovement*   Movement  = (UFloatingPawnMovement*)Owner->GetMovementComponent();
	TArray<UActorComponent*> WeaponArr = Owner->GetComponentsByClass(UWeaponComponent::StaticClass());
	//

	//StatDefaults todo data input
	static const float StopMovementValue = 0.00001f;
	static float DefaultSpeed = 600.0f;
	static float MinSpeed = 50.0f;
	//

	//Found Debuffs in map will be stored here.
	TArray<FDebuff> DebuffArr;

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
					TD_LOG(Warning, TEXT("Speed Debuffed: %f"), Movement->MaxSpeed);
				}
				else
				{
					//DefaultSpeed /= PowerToPercent;
					//Movement->MaxSpeed = DefaultSpeed >= MinSpeed ? DefaultSpeed : MinSpeed;
					Movement->MaxSpeed /= PowerToPercent;
					TD_LOG(Warning, TEXT("Speed Reset: %f"), Movement->MaxSpeed);
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
	else 	// Not Overlappable ( Stun, Snared, Taunt, Sleep, etc )
	{
		DebuffMap.MultiFind(InDebuff.Type, DebuffArr);

		bool bIsDebuffRemain = (DebuffArr.Num() != 0);

		switch ( InDebuff.Type )
		{
			case EDebuffType::Snared:
				if ( bIsDebuffRemain )
				{
					//Movement->Deactivate();
					if(bIsStopped)break;
					Movement->MaxSpeed *= StopMovementValue;
					TD_LOG(Warning, TEXT("Speed Debuffed: %f"), Movement->MaxSpeed);
					bIsStopped=true;
				}
				else
				{
					//Movement->Activate();
					if (!bIsStopped)break;
					Movement->MaxSpeed /= StopMovementValue;
					TD_LOG(Warning, TEXT("Speed Reset: %f"), Movement->MaxSpeed);
					bIsStopped=false;
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

bool UUnitDebuffComponent::IsDebuffTypeOverlappable(const EDebuffType & InDebuffType)
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

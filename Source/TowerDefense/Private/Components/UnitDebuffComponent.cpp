// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitDebuffComponent.h"
#include "TDCharacter.h"
#include "GameFramework\FloatingPawnMovement.h"
#include "WeaponComponent.h"
#include "TimerManager.h"

void UUnitDebuffComponent::RegDebuff(const FDebuff& InDebuff)
{
	bool bNeedUpdate = true;
	FDebuff* DebuffPtr;
	TArray<FTimerHandle>* HandlesPtr = BuffIDTimersMap.Find(InDebuff.ID);
	if (HandlesPtr)
	{
		// Find stacked debuff.
		DebuffPtr = BuffTypeDataMap.FindPair(InDebuff.Type, InDebuff);
		if (!DebuffPtr)
		{
			TD_LOG(Warning, TEXT("BuffTypeDataMap.FindPair returned nullptr. This should never happen. UnregDebuff() failed or something is wrong"));
			return;
		}
		
		if (InDebuff.MaxStack > DebuffPtr->CurrentStack)
		{
			// Stack InDebuff.
			DebuffPtr->CurrentStack += InDebuff.CurrentStack;

			// Validate Debuff stack count which should not over MaxStack
			DebuffPtr->CurrentStack = InDebuff.MaxStack < DebuffPtr->CurrentStack ? InDebuff.MaxStack : DebuffPtr->CurrentStack;

			// Each Debuff instance need timer to call UnregDebuff().
			HandlesPtr->Add(FTimerHandle());
		}
		else // MaxStack
		{
			const float DebuffRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(HandlesPtr->Last());
			if (InDebuff.Duration < DebuffRemaining)
			{
				// if InDebuff duration is lesser then debuff remaining time and debuff stack is max, there'no update.
				return;
			}

			bNeedUpdate = false;
		}
	}
	else // New Entry
	{
		HandlesPtr = &BuffIDTimersMap.Add(InDebuff.ID, TArray<FTimerHandle>());
		HandlesPtr->Add(FTimerHandle());
		DebuffPtr = &BuffTypeDataMap.Add(InDebuff.Type, InDebuff); 
	}	

	if (IsBlendable(InDebuff.Type))
	{
		FBuffModifier& BuffMod = BuffTypeModMap.FindOrAdd(InDebuff.Type);

		//Set Base value of modifier if not yet set.
		if (BuffMod.BaseVal == 0.0f)
		{
			////todo setter 만들고 Owner의 PostInitialzeComponents에서 set.
			TArray<UObject*> SubObjects;
			GetOwner()->GetDefaultSubobjects(SubObjects);

			if (InDebuff.Type == EDebuffType::Slow)
			{
				UFloatingPawnMovement* Movement = nullptr;
				SubObjects.FindItemByClass<UFloatingPawnMovement>(&Movement);
				BuffMod.BaseVal = Movement ? Movement->MaxSpeed : 400.0f;
			}
			//else...
		}
	}

	//Set debuff duration.
	GetWorld()->GetTimerManager().SetTimer(HandlesPtr->Last(), FTimerDelegate::CreateUFunction(this, FName("UnregDebuff"), *DebuffPtr), InDebuff.Duration, false);
	TD_LOG(Warning, TEXT("SetDebuffTimer"));

	//Apply Debuff
	if (bNeedUpdate)
	{
		UpdateStat(*DebuffPtr, true);
	}
}

void UUnitDebuffComponent::UnregDebuff(FDebuff& InDebuff)
{
	TD_LOG(Warning, TEXT("UnregDebuff"));

	UpdateStat(InDebuff, false);

	if ( IsBlendable(InDebuff.Type) || InDebuff.CurrentStack <= 1 )
	{ 
		BuffTypeDataMap.RemoveSingle(InDebuff.Type, InDebuff);
		BuffIDTimersMap.Remove(InDebuff.ID);
	}
	else
	{
		InDebuff.CurrentStack--;
		BuffIDTimersMap.Find(InDebuff.ID)->RemoveAt(0);
	}
}

void UUnitDebuffComponent::UpdateStat(const FDebuff& InDebuff, bool bDebuffOn)
{
	//CharacterStats
	const ATDCharacter*      Owner     = (ATDCharacter*)GetOwner();
	UFloatingPawnMovement*   Movement  = (UFloatingPawnMovement*)Owner->GetMovementComponent();
	TArray<UActorComponent*> WeaponArr = Owner->GetComponentsByClass(UWeaponComponent::StaticClass());
	//

	////임시
	static const float SnaredMoveSpeedModifier = 0.00001f;

	TArray<FDebuff> DebuffArr;

	// ( Slow, Exhaust { AttkSpd,MovementSpd }, etc )
	if ( IsBlendable(InDebuff.Type) )
	{
		//FDebuff* RegisteredDebuff = DebuffMap.FindPair(InDebuff.Type, InDebuff);

		//if (!RegisteredDebuff) return;

		FBuffModifier* BuffMod = BuffTypeModMap.Find(InDebuff.Type);
		if (!BuffMod)
		{
			TD_LOG(Warning, TEXT("No BuffMod!"));
			return;
		}
		const float ModifiedVal = BuffMod->SetModifier(InDebuff.bIsAdditive, bDebuffOn, InDebuff.PowerPerStack);

		switch ( InDebuff.Type )
		{
			case EDebuffType::Slow:
				Movement->MaxSpeed = ModifiedVal;
				TD_LOG(Warning, TEXT("Speed Modified: %f"), Movement->MaxSpeed);
				break;

			default:
				break;
		}
	}
	else // ( Stun, Snare, Taunt, Sleep, etc )
	{
		BuffTypeDataMap.MultiFind(InDebuff.Type, DebuffArr);

		bool bIsDebuffRemain = (DebuffArr.Num() != 0);

		switch ( InDebuff.Type )
		{
			case EDebuffType::Snared:
				if ( bIsDebuffRemain )
				{
					if (bIsStopped) break;
					Movement->MaxSpeed *= SnaredMoveSpeedModifier;
					TD_LOG(Warning, TEXT("Speed Debuffed: %f"), Movement->MaxSpeed);
					bIsStopped=true;
				}
				else
				{
					if (!bIsStopped) break;
					Movement->MaxSpeed /= SnaredMoveSpeedModifier;
					TD_LOG(Warning, TEXT("Speed Reset: %f"), Movement->MaxSpeed);
					bIsStopped=false;
				}
				break;

			case EDebuffType::Stun:
				if ( bIsDebuffRemain )
				{
					TD_LOG(Warning, TEXT("Stun"));
				}
				else
				{
					TD_LOG(Warning, TEXT("Stun End"));
				}				
				break;

			default:
				break;
		}
	}
}


bool UUnitDebuffComponent::IsBlendable(const EDebuffType& InDebuffType)
{
	switch (InDebuffType)
	{
		case EDebuffType::Slow:
			return true;

		case EDebuffType::Snared:
		case EDebuffType::Stun:
		default:
			return false;
	}
}

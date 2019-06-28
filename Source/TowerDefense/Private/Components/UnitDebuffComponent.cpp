// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitDebuffComponent.h"
#include "TDCharacter.h"
#include "GameFramework\FloatingPawnMovement.h"
#include "WeaponComponent.h"

void UUnitDebuffComponent::BeginPlay()
{
	//((ATDCharacter*)GetOwner())->GetTakeDamageDelegate()->AddDynamic(this,&UUnitDebuffComponent::TestFunc);
	//((ATDCharacter*)GetOwner())->GetTakeDamageDelegate().
}

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
		
		if (InDebuff.MaxStack > HandlesPtr->Num())
		{
			// Each Debuff instance need timer to Unreg itself.
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
			// Since this debuff is already applying maximum effect we do not update stat. We can just reset last Debuff duration.
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
			////todo:타이머에 영향을 줄 정도의 속도 문제가 있다면 아래 변수를 멤버로 TweakPtr에 저장. setter 만들고 Owner의 PostInitialzeComponents에서 set.
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

	//Apply Debuff
	if (bNeedUpdate)
	{
		UpdateStat(*DebuffPtr, true);
	}
}

void UUnitDebuffComponent::UnregDebuff(FDebuff& InDebuff)
{
	UpdateStat(InDebuff, false);

	auto TimersPtr = BuffIDTimersMap.Find(InDebuff.ID);

	if ( IsBlendable(InDebuff.Type) || TimersPtr->Num() <= 1 )
	{ 
		BuffTypeDataMap.RemoveSingle(InDebuff.Type, InDebuff);
		BuffIDTimersMap.Remove(InDebuff.ID);
	}
	else
	{
		TimersPtr->RemoveAt(0);
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
		FBuffModifier* BuffMod = BuffTypeModMap.Find(InDebuff.Type);
		if (!BuffMod)
		{
			TD_LOG(Warning, TEXT("No BuffMod!"));
			return;
		}
		const float ModifiedVal = BuffMod->SetModifier(InDebuff.bIsAdditive, bDebuffOn, InDebuff.Power);

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
					bIsStopped = true;
				}
				else
				{
					if (!bIsStopped) break;
					Movement->MaxSpeed /= SnaredMoveSpeedModifier;
					TD_LOG(Warning, TEXT("Speed Reset: %f"), Movement->MaxSpeed);
					bIsStopped = false;
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

void UUnitDebuffComponent::TakeDamage(const FDamage& InDamage)
{
	TD_LOG(Warning,TEXT("TESTFUNC"));
}

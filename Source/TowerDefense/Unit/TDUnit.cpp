// Fill out your copyright notice in the Description page of Project Settings.

#include "TDUnit.h"
#include "Engine\World.h"
#include "PaperSpriteComponent.h"
#include "AIModule\Classes\AIController.h"
#include "AIModule\Classes\BrainComponent.h"
#include "Engine\Public\TimerManager.h"
#include "FlipbookShakingComponent.h"
#include "Tower.h"
#include "TDPlayerStateBase.h"
#include "TDUnitCommonData.h"

ATDUnit::ATDUnit()
{
	Shadow = CreateOptionalDefaultSubobject<UPaperSpriteComponent>("Shadow");
	Shadow->SetupAttachment(GetRootComponent());
}

bool ATDUnit::UpdateAnimation()
{
	UPaperFlipbook* DesiredAnim = Common->FlipbookMap.Find(UnitState)->Get();

	if (DesiredAnim)
	{
		GetSprite()->SetFlipbook(DesiredAnim);
		return true;
	}
	else return false;

}

void ATDUnit::Tick(float DeltaTime)
{
	if (GetVelocity().X >0)
	{
		Shadow->SetRelativeRotation(FRotator(180,0,-90));
		GetSprite()->SetRelativeRotation(FRotator(180, 0, -90));
	}
	else if (GetVelocity().X < 0)
	{
		Shadow->SetRelativeRotation(FRotator(0, 0, 0));
		GetSprite()->SetRelativeRotation(FRotator(0, 0, -90));
	}
	//if (UnitState == EUnitState::Dead)
	//{
	//// Fade or something
	//	//FTimerHandle  handle;
	//	//GetWorld()->GetTimerManager().SetTimer(handle, [this]() {
	//	//	Destroy();
	//	//}, 3.5f, 1);
	//}
}

void ATDUnit::ChangeState(EUnitState InState)
{
	UnitState = InState;
	UpdateAnimation();
}

void ATDUnit::ApplyDamage(float ShakePower, float ShakeDuration, int32 Damage)
{
	if(UnitState == EUnitState::Dead)return;

	UnitHP-=Damage;

	if(UnitHP<=0) {	ChangeState (EUnitState::Dying); 
	PrimaryActorTick.bCanEverTick = false;
	((AAIController*)GetController())->GetBrainComponent()->StopLogic("Dead");
	Team=EUnitTeam::None;
	GetSprite()->SetLooping(false);
	CharacterDestroy();
	return;
	}
	
	auto ShakeComp = GetComponentByClass(UFlipbookShakingComponent::StaticClass());
	if(ShakeComp) ShakeComp->DestroyComponent();

	ShakeComp = NewObject<UFlipbookShakingComponent>(this,"FlipbookShakingComponent");
	Cast<UFlipbookShakingComponent>(ShakeComp)->Initialize(ShakePower, ShakeDuration);
	ShakeComp->RegisterComponent();
	AddOwnedComponent(ShakeComp);
}

void ATDUnit::CharacterDestroy_Implementation()
{
	UnitState = EUnitState::Dead;
	FTimerHandle  handle;
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {
		Destroy(); /* or pool */
	}, GetSprite()->GetFlipbookLength() + 3.5f, 1);
}

void ATDUnit::StartAttack()
{
	IsDelayChecking=true;
	execAttack_Implementation();
	GetWorldTimerManager().SetTimer(ActionTimerHandle,this, &ATDUnit::execAttack_Implementation, UnitAttackDelay,true);
}

void ATDUnit::execAttack_Implementation()
{
	IsDelayChecking = false;
	if (UnitState != EUnitState::Attacking)
	{
		GetWorldTimerManager().ClearTimer(ActionTimerHandle);
		return;
	}
	//if(AggroTarget)
	//{
	//execAttack();
	//}
}


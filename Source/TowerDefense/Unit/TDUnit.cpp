// Fill out your copyright notice in the Description page of Project Settings.

#include "TDUnit.h"
#include "PaperSpriteComponent.h"
#include "TimerManager.h"
#include "FlipbookShakingComponent.h"
#include "MeleeAttackComponent.h"
#include "TDPlayerStateBase.h"
#include "TDUnitCommonData.h"

ATDUnit::ATDUnit()
{
	Shadow = CreateOptionalDefaultSubobject<UPaperSpriteComponent>("Shadow");
	Shadow->SetupAttachment(GetRootComponent());
	//AttackComp = CreateDefaultSubobject<UMeleeAttackComponent>("AttackComponent");
	//AddOwnedComponent(AttackComp);
	
}

void ATDUnit::BeginPlay()
{
	Super::BeginPlay();

	if(!(AttackCompClass.Get()))return;
	AttackComp = NewObject<UAttackComponent>(this, AttackCompClass.Get());
	AddOwnedComponent(AttackComp);

	InitializeTDComponents();
}

bool ATDUnit::UpdateAnimation()
{
	UPaperFlipbook* DesiredAnim = Common->FlipbookMap.Find(UnitState)->Get();

	if (DesiredAnim)
	{
		GetSprite()->SetFlipbook(DesiredAnim);

		if (UnitState != EUnitState::Running) {	GetSprite()->SetLooping(false);}
		else {GetSprite()->SetLooping(true);}

		GetSprite()->PlayFromStart();

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
}

void ATDUnit::ChangeState(EUnitState InState)
{
	UnitState = InState;
	UpdateAnimation();
}

//void ATDUnit::StartAttack()
//{
//	IsDelayChecking=true;
//
//	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("StartAttack"));
//	AttackGuider();
//	GetWorldTimerManager().SetTimer(ActionTimerHandle,this, &ATDUnit::AttackGuider, UnitAttackDelay,true);
//}
//
//void ATDUnit::AttackGuider()
//{
//
////	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("GuiderCall"));
//	IsDelayChecking = false;
//
//	if (UnitState == EUnitState::Attacking && IsValid(AggroTarget) )
//	{
//		if (AggroTarget->UnitState == EUnitState::Dead) {goto EndOfLogic;}
//
//		UpdateAnimation();
//		ExecuteAttack();
//		IsDelayChecking = true;
//		return;
//	}
//
//EndOfLogic:
//
//	AggroTarget=nullptr;
//	GetWorldTimerManager().ClearTimer(ActionTimerHandle);
////	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("End Of Logic"));
//}


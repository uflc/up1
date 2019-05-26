// Fill out your copyright notice in the Description page of Project Settings.

#include "TDUnit.h"
#include "TDUnitCommonData.h"
#include "PaperFlipbook.h" //anim
#include "PaperFlipbookComponent.h" //anim
#include "PaperSpriteComponent.h" //shadow
#include "WeaponComponent.h"
#include "TDWeaponCommonData.h"

ATDUnit::ATDUnit()
{
	Animation = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook Animation"));
	//TD에서는 XY평면을 쓸 것이기 때문에 스프라이트 롤을 90도 돌린다.
	Animation->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.f));
	
	RootComponent = Animation;

	Shadow = CreateOptionalDefaultSubobject<UPaperSpriteComponent>(TEXT("Shadow"));

	if (Shadow)
	{
		Shadow->SetupAttachment(Animation);
	}

	//AttackComp = CreateDefaultSubobject<UMeleeAttackComponent>("AttackComponent");
	//AddOwnedComponent(AttackComp);
}

void ATDUnit::BeginPlay()
{
	Super::BeginPlay();

	// Create AttackComponent(Weapon) from UnitCommonData
	if (!Common->WeaponData) return;
	if (!AttackComp->IsValidLowLevelFast()) 
	{
		AttackCompClass = Common->WeaponData->GetWeaponClass();
		AttackComp = NewObject<UWeaponComponent>(this, AttackCompClass);
	}
	AddOwnedComponent(AttackComp);
	AttackComp->SetCommonData(Common->WeaponData);

	//InitializeTDComponents();
}

UPaperFlipbook * ATDUnit::GetDesiredAnimation()
{
	return Common ? Common->Animations[(uint8)UnitState].Get() : nullptr;
}

bool ATDUnit::UpdateAnimation()
{
	UPaperFlipbook* DesiredAnim = GetDesiredAnimation();

	if (DesiredAnim)
	{
		Animation->SetFlipbook(DesiredAnim);
		return true;
	}
	
	return false;
}

void ATDUnit::ChangeState(EUnitState InState)
{
	UnitState = InState;
	UpdateAnimation();
}

void ATDUnit::UpdateDirection()
{

}

bool ATDUnit::IsTargetable()
{
	if (UnitState==EUnitState::Dying || UnitState == EUnitState::Dead) return false;

	return true;
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


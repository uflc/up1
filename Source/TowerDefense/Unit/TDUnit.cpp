// Fill out your copyright notice in the Description page of Project Settings.

#include "TDUnit.h"
#include "TDUnitCommonData.h"
#include "PaperFlipbook.h" //anim
#include "PaperFlipbookComponent.h" //anim
#include "PaperSpriteComponent.h" //shadow
#include "DirectWeaponComponent.h"


ATDUnit::ATDUnit()
{
	//@TODO 캡슐 삭제? 플립북 루트?

	Shadow = CreateOptionalDefaultSubobject<UPaperSpriteComponent>("Shadow");
	Shadow->SetupAttachment(GetSprite());

	//언리얼 기본 스프라이트는 XZ 평면을 쓰지만 TD에서는 XY평면을 쓸 것이기 때문에 스프라이트 롤을 90도 돌린다.
	GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.f));

	static FName TDCollisionProfileName(TEXT("OverlapOnlyTDUnit"));
	GetSprite()->SetCollisionProfileName(TDCollisionProfileName);

	//AttackComp = CreateDefaultSubobject<UMeleeAttackComponent>("AttackComponent");
	//AddOwnedComponent(AttackComp);
}

void ATDUnit::BeginPlay()
{
	Super::BeginPlay();

	if(!(AttackCompClass.Get())) return;
	AttackComp = NewObject<UWeaponComponent>(this, AttackCompClass.Get());
	AddOwnedComponent(AttackComp);

	InitializeTDComponents();
}

UPaperFlipbook * ATDUnit::GetDesiredAnimation()
{
	return Common->FlipbookMap.Find(UnitState)->Get();
}

bool ATDUnit::UpdateAnimation()
{
	UPaperFlipbook* DesiredAnim = GetDesiredAnimation();

	if (DesiredAnim)
	{
		GetSprite()->SetFlipbook(DesiredAnim);
		return true;
	}
	else return false;

}

void ATDUnit::ChangeState(EUnitState InState)
{
	UnitState = InState;
	UpdateAnimation();
}

void ATDUnit::UpdateDirection()
{

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


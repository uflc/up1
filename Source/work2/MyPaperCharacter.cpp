// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPaperCharacter.h"
#include "FlipbookShakingComponent.h"
#include "BehaviorTree\BehaviorTreeComponent.h"
#include "Tower.h"
#include "MyPaperCharacterCommon.h"


bool AMyPaperCharacter::UpdateAnimation()
{
	UPaperFlipbook* DesiredAnim = Common->FlipbookMap.Find(UnitState)->Get();


	if (DesiredAnim)
	{
		GetSprite()->SetFlipbook(DesiredAnim);
		return true;
	}
	else return false;

}

void AMyPaperCharacter::ChangeState(EUnitState InState)
{
	UnitState = InState;
	UpdateAnimation();
}

void AMyPaperCharacter::ApplyDamage(float ShakePower, float ShakeDuration, int32 Damage)
{
	UnitHP-=Damage;
	if(UnitHP<=0) {ChangeState (EUnitState::Dying); return;}
	
	auto ShakeComp = GetComponentByClass(UFlipbookShakingComponent::StaticClass());
	if(ShakeComp) ShakeComp->DestroyComponent();

	ShakeComp = NewObject<UFlipbookShakingComponent>(this,"FlipbookShakingComponent");
	Cast<UFlipbookShakingComponent>(ShakeComp)->Initialize(ShakePower, ShakeDuration);
	ShakeComp->RegisterComponent();
	AddOwnedComponent(ShakeComp);
}

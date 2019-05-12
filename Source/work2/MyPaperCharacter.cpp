// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPaperCharacter.h"
#include "Engine\World.h"
#include "AIModule\Classes\AIController.h"
#include "AIModule\Classes\BrainComponent.h"
#include "Engine\Public\TimerManager.h"
#include "FlipbookShakingComponent.h"
#include "Tower.h"
#include "TDPlayerStateBase.h"
#include "TDUnitCommonData.h"


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

void AMyPaperCharacter::Tick(float DeltaTime)
{
	//if (UnitState == EUnitState::Dead)
	//{
	//// Fade or something
	//	//FTimerHandle  handle;
	//	//GetWorld()->GetTimerManager().SetTimer(handle, [this]() {
	//	//	Destroy();
	//	//}, 3.5f, 1);
	//}
}

void AMyPaperCharacter::ChangeState(EUnitState InState)
{
	UnitState = InState;
	UpdateAnimation();
}

void AMyPaperCharacter::ApplyDamage(float ShakePower, float ShakeDuration, int32 Damage)
{
	if(UnitState == EUnitState::Dead)return;

	UnitHP-=Damage;
	if(UnitHP<=0) {ChangeState (EUnitState::Dying); 
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

void AMyPaperCharacter::CharacterDestroy_Implementation()
{
	UnitState = EUnitState::Dead;
	FTimerHandle  handle;
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {
		Destroy(); /* or pool */
	}, GetSprite()->GetFlipbookLength() + 3.5f, 1);
}

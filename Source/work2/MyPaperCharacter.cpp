// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPaperCharacter.h"
#include "Engine\World.h"
#include "FlipbookShakingComponent.h"
#include "BehaviorTree\BehaviorTreeComponent.h"
#include "Tower.h"
#include "GameFramework\Controller.h"
#include "AIController.h"
#include "MyPaperCharacterCommon.h"
#include "TDPlayerStateBase.h"

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
	if (UnitState == EUnitState::Dead)
	{
	// Fade or something
		//FTimerHandle  handle;
		//GetWorld()->GetTimerManager().SetTimer(handle, [this]() {
		//	Destroy();
		//}, 3.5f, 1);
	}
}

void AMyPaperCharacter::ChangeState(EUnitState InState)
{
	UnitState = InState;
	UpdateAnimation();
}

void AMyPaperCharacter::ApplyDamage(float ShakePower, float ShakeDuration, int32 Damage)
{
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
	FTimerHandle  handle;
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {
		ChangeState(EUnitState::Dead);
		Destroy(); /* or pool */
	}, GetSprite()->GetFlipbookLength() + 3.5f, 1);
}

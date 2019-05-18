// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCharacter.h"
#include "PaperSpriteComponent.h"
#include "TDUnitCommonData.h"
#include "TimerManager.h"
#include "FlipbookShakingComponent.h"
#include "AIController.h"


void ATDCharacter::Tick(float DeltaTime)
{
	if (GetVelocity().X > 0)
	{
		Shadow->SetRelativeRotation(FRotator(180, 0, -90));
		GetSprite()->SetRelativeRotation(FRotator(180, 0, -90));
	}
	else if (GetVelocity().X < 0)
	{
		Shadow->SetRelativeRotation(FRotator(0, 0, 0));
		GetSprite()->SetRelativeRotation(FRotator(0, 0, -90));
	}
}

bool ATDCharacter::ChangeAnimation()
{
	if (!Super::ChangeAnimation()) return false;

	//if (UnitState != EUnitState::Running) {	GetSprite()->SetLooping(false);}
			//else {GetSprite()->SetLooping(true);}

			//GetSprite()->PlayFromStart();
	return true;
}

void ATDCharacter::TDUnitTakeDamage(float ShakePower, float ShakeDuration, int32 Damage)
{
	// Already dying or dead
	if (UnitState == EUnitState::Dead || UnitState == EUnitState::Dying) return;

	// 사망.
	Health -= Damage;
	if (Health <= 0)  Die();

	// FlipbookShakingComponent 효과
	auto ShakeComp = GetComponentByClass(UFlipbookShakingComponent::StaticClass());
	if (ShakeComp) ShakeComp->DestroyComponent();

	ShakeComp = NewObject<UFlipbookShakingComponent>(this, "FlipbookShakingComponent");
	Cast<UFlipbookShakingComponent>(ShakeComp)->Initialize(ShakePower, ShakeDuration);
	ShakeComp->RegisterComponent();
	AddOwnedComponent(ShakeComp);
}

void ATDCharacter::Die_Implementation()
{
	// Play Dying anim just once
	ChangeState(EUnitState::Dying);
	GetSprite()->SetLooping(false);

	// prevent BTService Aggro Check trace checked
	Team = EUnitTeam::None;

	// detach the controller
	if (Controller != nullptr)
	{
		//Controller->UnPossess(); //testing if this affect ai logic
		Controller->Destroy();
	}

	// After Dying anim 사후경직
	FTimerHandle  Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &ATDCharacter::OnDeath, GetSprite()->GetFlipbookLength(), false);
}

void ATDCharacter::OnDeath()
{
	ChangeState(EUnitState::Dead);

	SetLifeSpan(3.5f); //@TODO: do not hard code life span?
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCharacter.h"
#include "TDUnitCommonData.h"
#include "PaperSpriteComponent.h" //shadow
#include "PaperFlipbookComponent.h" //anim
#include "FlipbookShakingComponent.h"
#include "TimerManager.h"
#include "AIController.h"


void ATDCharacter::Tick(float DeltaTime)
{
	UpdateDirection();
}

bool ATDCharacter::UpdateAnimation()
{
	if (!Super::UpdateAnimation()) return false;

	return true;
}

void ATDCharacter::UpdateDirection()
{	//��������Ʈ ���� ��ȯ. //@TODO any Event?
	if (GetVelocity().X > 0)
	{
		Shadow->SetRelativeRotation(FRotator(180, 0, -90));
		GetSprite()->SetRelativeRotation(FRotator(180, 0, -90));
	}
	else if (GetVelocity().X < 0) // ���� �� ���� ���� �ִ� ���� ����ؾ���
	{
		Shadow->SetRelativeRotation(FRotator(0, 0, 0));
		GetSprite()->SetRelativeRotation(FRotator(0, 0, -90));
	}
}

void ATDCharacter::TDUnitTakeDamage(float ShakePower, float ShakeDuration, int32 Damage)
{
	// Already dying or dead
	if (UnitState == EUnitState::Dead || UnitState == EUnitState::Dying) return;

	// ���.
	Health -= Damage;
	if (Health <= 0)  Die();

	// FlipbookShakingComponent ȿ��
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

	// After Dying anim ���İ���
	FTimerHandle  Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &ATDCharacter::OnDeath, GetSprite()->GetFlipbookLength(), false);
}

void ATDCharacter::OnDeath()
{
	ChangeState(EUnitState::Dead);

	SetLifeSpan(3.5f); //@TODO: 
}


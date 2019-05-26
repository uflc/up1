// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCharacter.h"
#include "TDCharData.h"
//#include "PaperSpriteComponent.h" //shadow
#include "PaperFlipbookComponent.h" //anim
#include "FlipbookShakingComponent.h"
#include "TimerManager.h"
#include "AIController.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "TowerDefense.h"

ATDCharacter::ATDCharacter()
{
	static FName TDCollisionProfileName(TEXT("OverlapOnlyTDUnit"));
	Animation->SetCollisionProfileName(TDCollisionProfileName);

	Movement = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("Movement"));
	Movement->UpdatedComponent = Animation;
}

void ATDCharacter::BeginPlay()
{
	Super::BeginPlay();

	UTDCharData* CharData = Cast<UTDCharData>(Common);

	if (CharData)
	{
		AggroDrawnRange = CharData->DefaultAggroDrawnRange;
		DrawingAggroRange = CharData->DefaultDrawingAggroRange;
	}
}

void ATDCharacter::Tick(float DeltaTime)
{
	UpdateDirection();
}

void ATDCharacter::UpdateDirection()
{	
	if (GetVelocity().X > 0)
	{
		//Shadow->SetRelativeRotation(FRotator(180, 0, -90));
		Animation->SetRelativeRotation(FRotator(180, 0, -90));
	}
	else if (GetVelocity().X < 0) // 멈출 때 원래 보고 있던 방향 기억해야함 // ?
	{
		//Shadow->SetRelativeRotation(FRotator(0, 0, 0));
		Animation->SetRelativeRotation(FRotator(0, 0, -90));
	}
}


bool ATDCharacter::UpdateAnimation()
{
	if (!Super::UpdateAnimation()) return false;

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
	Animation->SetLooping(false);
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
	GetWorldTimerManager().SetTimer(Timer, this, &ATDCharacter::OnDeath, Animation->GetFlipbookLength(), false);
}

void ATDCharacter::OnDeath()
{
	ChangeState(EUnitState::Dead);

	SetLifeSpan(3.5f); //@TODO: 
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCharacter.h"
#include "TDCharData.h"
#include "PaperFlipbookComponent.h" //anim
#include "FlipbookShakingComponent.h"
#include "TimerManager.h"
#include "AIController.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "TowerDefense.h"
#include "UnitDebuffComponent.h"

ATDCharacter::ATDCharacter()
{
	static FName TDCollisionProfileName(TEXT("OverlapOnlyTDUnit"));
	Animation->SetCollisionProfileName(TDCollisionProfileName);

	Movement = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("Movement"));
	//Movement->
	Movement->UpdatedComponent = Animation;

	DebuffControll = CreateDefaultSubobject<UUnitDebuffComponent>(TEXT("DebuffController"));
	//DebuffControll->
}

void ATDCharacter::BeginPlay()
{
	Super::BeginPlay();

	UTDCharData* CharData = Cast<UTDCharData>(UnitData);

	if (CharData)
	{
		AggroDrawnRange = CharData->GetAggroDrawnRange();
		DrawingAggroRange = CharData->GetDrawingAggroRange();
		Health = CharData->GetHealth();
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
		Animation->SetRelativeRotation(FRotator(-180, 0, -90));
	}
	else if (GetVelocity().X < 0) // 멈출 때 원래 보고 있던 방향 기억해야함 // ?
	{
		Animation->SetRelativeRotation(FRotator(0, 0, -90));
	}
}

bool ATDCharacter::IsLethal()
{
	return UnitState == EUnitState::Dead || UnitState == EUnitState::Dying;
}


bool ATDCharacter::UpdateAnimation()
{
	if (!Super::UpdateAnimation()) return false;

	return true;
}

void ATDCharacter::TDUnitTakeDamage(float ShakePower, float ShakeDuration, int32 Damage)
{
	if (IsLethal()) return;

	// 사망.
	Health -= Damage;
	if (Health <= 0)
	{
		Die();
	}

	// FlipbookShakingComponent 효과 //TODO 효과적인 방법?
	UActorComponent* ShakeComp = GetComponentByClass(UFlipbookShakingComponent::StaticClass());
	if (ShakeComp)
	{
		ShakeComp->DestroyComponent();
	}
	ShakeComp = NewObject<UFlipbookShakingComponent>(this, "FlipbookShakingComponent");
	Cast<UFlipbookShakingComponent>(ShakeComp)->Initialize(ShakePower, ShakeDuration);
	ShakeComp->RegisterComponent();
	AddOwnedComponent(ShakeComp);
}

void ATDCharacter::TDUnitTakeDebuff(FDebuff& InDebuff)
{
	if (IsLethal()) return;
	DebuffControll->RegDebuff(InDebuff);
}

void ATDCharacter::Die_Implementation()
{
	// Play Dying anim once
	ChangeState(EUnitState::Dying);
	Animation->SetLooping(false);

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


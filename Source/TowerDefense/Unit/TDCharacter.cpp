// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCharacter.h"
#include "TDCharData.h"
#include "PaperFlipbookComponent.h" //anim
#include "PaperFlipbook.h"
#include "FlipbookShakingComponent.h"
#include "TimerManager.h"
#include "AIController.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "UnitDebuffComponent.h"
#include "WidgetComponent.h"
#include "TDCharWidget.h"
#include "Sound\SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "TowerDefense.h"


ATDCharacter::ATDCharacter()
{
	Movement = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("Movement"));

	static FName TDCharCollisionProfileName(TEXT("TDPawn"));
	Box->SetCollisionProfileName(TDCharCollisionProfileName);
	static const FVector BoxExtent(32.0f, 32.0f, 1.0f);
	Box->InitBoxExtent(BoxExtent);

	static const FVector SpriteOffset(-15.0f, -50.0f, 0.0f);
	Animation->SetCollisionProfileName(TDCharCollisionProfileName);
	Animation->SetRelativeLocation(SpriteOffset);
	Animation->SetupAttachment(Box);

	DebuffControll = CreateDefaultSubobject<UUnitDebuffComponent>(TEXT("DebuffController"));

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget0_HealthBar"));
	HealthBar->SetupAttachment(Box);
	HealthBar->SetRelativeLocation(SpriteOffset);
	HealthBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarWidget(TEXT("WidgetBlueprint'/Game/Blueprint/UI/CharacterHealthBar.CharacterHealthBar_C'"));
	if (HealthBarWidget.Succeeded())
	{
		HealthBar->SetWidgetClass(HealthBarWidget.Class);
		HealthBar->SetDrawAtDesiredSize(true);
	}
}

void ATDCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATDCharacter::Tick(float DeltaTime)
{
	UpdateDirection();
}

void ATDCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UTDCharData* CharData = Cast<UTDCharData>(UnitData);
	if (CharData)
	{
		AggroDrawnRange = CharData->GetAggroDrawnRange();
		DrawingAggroRange = CharData->GetDrawingAggroRange();
		Health = CharData->GetHealth();
	}

	//Without calling this HealthBar->GetUserWidgetObject() returns nullptr for some reason. don't know why.
	HealthBar->InitWidget();
	UTDCharWidget* HealthBarWidget = Cast<UTDCharWidget>(HealthBar->GetUserWidgetObject());
	if (HealthBarWidget)
	{
		HealthBarWidget->SetOwner(this);
	}
	else
	{
		TD_LOG(Warning, TEXT("err Init %s"), *HealthBar->GetWidgetClass()->GetName());
	}
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
	OnHealthChanged.Broadcast();
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
	
	USoundBase* Sound = nullptr;

	bool bIsDyingSoundExist = UnitData->GetSounds().IsValidIndex((uint8)ESoundType::Dying);

	if ( bIsDyingSoundExist )
	{
		Sound = ( UnitData ? UnitData->GetSounds()[(uint8)ESoundType::Dying].Get() : nullptr );
	}

	if ( Sound != nullptr )
	{
		UGameplayStatics::PlaySound2D((UObject*)GetWorld(), Sound, 1, 1, 0);
	}

	// detach the controller
	if (Controller != nullptr)
	{
		//Controller->UnPossess(); //testing if this affect ai logic
		Controller->Destroy();
	}

	if (HealthBar != nullptr)
	{
		HealthBar->DestroyComponent();
	}

	// After Dying anim 사후경직
	FTimerHandle  Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &ATDCharacter::OnDeath, Animation->GetFlipbookLength(), false);
}

void ATDCharacter::OnDeath_Implementation()
{
	ChangeState(EUnitState::Dead);

	SetLifeSpan(3.5f); //@TODO: 
}

float ATDCharacter::GetAggroRange() const
{
	return AggroDrawnRange != 0.0f ? AggroDrawnRange : Super::GetAggroRange();
}


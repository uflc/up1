// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCharacter.h"
#include "TDCharData.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbook.h"
#include "Components/TDPaperFlipbookComponent.h" //anim
#include "WidgetComponent.h"
#include "TDCharWidget.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "UnitDebuffComponent.h"
#include "Sound\SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "AIController.h"
#include "ShakingComponent.h"
#include "TowerDefense.h"


ATDCharacter::ATDCharacter()
{
	Movement = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("Movement"));

	static FName TDCharCollisionProfileName(TEXT("TDPawn"));
	static const FVector BoxExtent(4.0f, 4.0f, 1.0f);
	Box->SetCollisionProfileName(TDCharCollisionProfileName);
	Box->InitBoxExtent(BoxExtent);

	static FName TDCharAnimCollisionProfileName(TEXT("CharacterMesh"));
	static const FVector SpriteOffset(-15.0f, -50.0f, 0.0f);
	Animation->SetCollisionProfileName(TDCharAnimCollisionProfileName);
	Animation->SetRelativeLocation(SpriteOffset);

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
	const FVector& VelocityCopy = GetVelocity();

	const static FRotator RightRot(-180.f, 0.f, -90.f);
	const static FRotator LeftRot(0.f, 0.f, -90.f);

	if (VelocityCopy.X > 0)
	{
		Animation->SetRelativeRotation(RightRot);
	}
	else if (VelocityCopy.X < 0)
	{
		Animation->SetRelativeRotation(LeftRot);
	}
	//멈췄을 때는 원래 방향 그대로 있어야 하므로 업데이트 하지 않음.
}

bool ATDCharacter::IsLethal()
{
	ETDAnimState State = Animation->GetState();
	return  State == ETDAnimState::Dead || State == ETDAnimState::Dying;
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

	// Shaking 효과 //todo defaultsubobject better?
	UActorComponent* ShakeComp = GetComponentByClass(UShakingComponent::StaticClass());
	if (!ShakeComp)
	{
		ShakeComp = NewObject<UShakingComponent>(this, "ShakingComponent");
		if (!ShakeComp)
		{
			return;
		}
	}

	Cast<UShakingComponent>(ShakeComp)->Initialize(ShakePower, ShakeDuration);
}

void ATDCharacter::TDUnitTakeDebuff(FDebuff& InDebuff)
{
	if (IsLethal()) return;

	DebuffControll->RegDebuff(InDebuff);
}

void ATDCharacter::Die_Implementation()
{
	// Play Dying anim once
	Animation->ChangeState(ETDAnimState::Dying);
	Animation->PlayFromStart();
	
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

	if (Box)
	{
		Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (Animation)
	{
		Animation->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
	Animation->ChangeState(ETDAnimState::Dead);

	const static float DeadBodyRemainTime = 3.5f;
	SetLifeSpan(DeadBodyRemainTime);
}

float ATDCharacter::GetAggroRange() const
{
	return AggroDrawnRange != 0.0f ? AggroDrawnRange : Super::GetAggroRange();
}

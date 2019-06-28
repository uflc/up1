// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCharacter.h"
#include "TDCharData.h"
#include "PaperFlipbook.h"
#include "Components/TDPaperFlipbookComponent.h" //anim
#include "PaperSpriteComponent.h"
#include "WidgetComponent.h"
#include "TDCharWidget.h"
#include "UnitDebuffComponent.h"
#include "ShakingComponent.h"


ATDCharacter::ATDCharacter()
{
	Movement = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("Movement"));

	static FName TDCharCollisionProfileName(TEXT("TDPawn"));
	static const FVector BoxExtent(8.0f, 4.0f, 1.0f);
	Box->SetCollisionProfileName(TDCharCollisionProfileName);
	Box->InitBoxExtent(BoxExtent);

	static FName TDCharAnimCollisionProfileName(TEXT("CharacterMesh"));
	//static const FVector SpriteOffset(-15.0f, -50.0f, 5.0f);
	Animation->SetCollisionProfileName(TDCharAnimCollisionProfileName);
	//Animation->SetRelativeLocation(SpriteOffset);
	if (Shadow)
	{
		Shadow->SetRelativeLocation(FVector(0.0f, -0.1f, 0.0f));
	}

	DebuffControll = CreateDefaultSubobject<UUnitDebuffComponent>(TEXT("DebuffController"));
	OnTakeDamage.AddDynamic(DebuffControll, &UUnitDebuffComponent::TakeDamage);


	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget0_HealthBar"));
	HealthBar->SetWidgetSpace(EWidgetSpace::World);
	HealthBar->SetRelativeRotation(FRotator(90.0f, 90.0f, 0.0f));
	HealthBar->SetRelativeLocation(FVector(0.0f, -120.0f, 1.0f));
	HealthBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarWidget(TEXT("WidgetBlueprint'/Game/Blueprint/UI/CharacterHealthBar.CharacterHealthBar_C'"));
	if (HealthBarWidget.Succeeded())
	{
		HealthBar->SetWidgetClass(HealthBarWidget.Class);
		HealthBar->SetDrawSize(FVector2D(60.0f, 12.5f));
	}

	HealthBar->SetupAttachment(Box);
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

void ATDCharacter::Tick(float DeltaTime)
{
	UpdateDirection();
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
	OnTakeDamage.Broadcast(FDamage());
	if (Health <= 0)
	{
		Die();
		//todo OnDied.Broadcast()
		return;
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

#pragma once

#include "CoreMinimal.h"
#include "TDTypes.generated.h"

//@TODO End 추가 타입

UENUM(BlueprintType)
enum class EUnitTeam : uint8
{
	None	UMETA(DisplayName = "None"),
	Player	UMETA(DisplayName = "Player"),
	Enemy	UMETA(DisplayName = "Enemy"),
};

//TDUnit의 애니메이션 타입
UENUM(BlueprintType)
enum class EUnitState : uint8
{
	Idle		UMETA(DisplayName = "Idle Animation"),
	Attacking	UMETA(DisplayName = "Attaking Animation"),
	Running		UMETA(DisplayName = "Running Animation"),
	Dying		UMETA(DisplayName = "Dying Animation"),
	Dead		UMETA(DisplayName = "Dead Animation")
};

UENUM(BlueprintType)
enum class EWeaponFlipbookType : uint8
{
	Projectile,
	Effect	
};

UENUM(BlueprintType)
enum class EDirection : uint8
{
	LD	UMETA(DisplayName = "Left Dowm"),
	LT  UMETA(DisplayName = "Left Top"),
	RD	UMETA(DisplayName = "Right Down"),
	RT  UMETA(DisplayName = "Right Top"),
};


//타워 업그레이드 타입
UENUM(BlueprintType)
enum class ETowerType : uint8
{
	ONE,
	TWO,
	THREE
};

UENUM(BlueprintType)
enum class EDebuffType : uint8
{
	Stun,
	Snared,
	Slow
};

//불필요?
UENUM(BlueprintType)
enum class EValueType : uint8
{
	Coin		UMETA(DisplayName = "Player Coin"),
	Life 		UMETA(DisplayName = "Player Life"),
	Mana		UMETA(DisplayName = "Player Mana"),
	//HeroHP		UMETA(DisplayName = "HeroHP")
};

USTRUCT(BlueprintType)
struct  FDebuff
{
	GENERATED_BODY()

public:
	//Debuffs with same Type are considered to be blendable if not exclusive.
	//This will affect BT logic.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDebuffType Type;
	
	// if > 1, will be applied over time 
	////uint8 TickCount = 1; //TickInterval = Duration / TickCount

	// Sec
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	// if true power is additive modifier, false is multiplication modifier.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAdditive;

	//// bool bIsPrimary;

	// 0 ~100
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Power;

	// 0 ~100
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PowerPerStack;

	//Unique ID for a Debuff Ability. Debuffs with same ID are considered as same Debuff,
	//means when same debuff is applied, it might be stacked or discarded or replace old one.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxStack;

	// It also means how much do you stacking in registered one
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentStack;

	// 0 ~100
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DebuffChance;

	bool operator == (const FDebuff& InDebuff) 
	{
		//return ( (Type == InDebuff.Type) && ( Duration == InDebuff.Duration ) && ( Power == InDebuff.Power) && ( ID == InDebuff.ID) );

		return ( ID == InDebuff.ID );
	}
};


#define	 UPGRADES_NUM 3//TODO use Enum as Byte as arrry index ?
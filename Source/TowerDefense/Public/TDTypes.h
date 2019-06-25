#pragma once

#include "TDTypes.generated.h"


UENUM(BlueprintType)
enum class EUnitTeam : uint8
{
	None	UMETA(DisplayName = "None"),
	Player	UMETA(DisplayName = "Player"),
	Enemy	UMETA(DisplayName = "Enemy"),
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

//TDUnit의 애니메이션 타입
UENUM(BlueprintType)
enum class ETDAnimState : uint8
{
	Idle		UMETA(DisplayName = "Idle Animation"),
	Attacking	UMETA(DisplayName = "Attaking Animation"),
	Running		UMETA(DisplayName = "Running Animation"),
	Dying		UMETA(DisplayName = "Dying Animation"),
	Dead		UMETA(DisplayName = "Dead Animation")
};

UENUM(BlueprintType)
enum class ESoundType : uint8
{
	Dying		UMETA(DisplayName = "Dying Sound")
	//...
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

#define	 UPGRADES_NUM 3//TODO use Enum as Byte as arrry index ?

UENUM(BlueprintType)
enum class EDebuffType : uint8
{
	Stun,
	Snared,
	Slow
};

USTRUCT(BlueprintType)
struct FDebuff
{
	GENERATED_BODY()

public:
	//Unique ID for a Debuff Ability. Debuffs with same ID are considered as same Debuff,
	//means when same debuff is applied, it might be stacked or discarded or replace old one.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ID;

	//Debuffs with same Type are considered to be blendable if not exclusive.
	////This will affect BT logic.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDebuffType Type;

	//// bool bIsPrimary;

	// if true power is additive modifier, false is multiplication modifier.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAdditive;

	// As Multipication modifier, this is percent.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Power;

	// Sec
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	// if > 1, will be applied over time 
	////uint8 TickCount = 1; //TickInterval = Duration / TickCount

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 MaxStack;

	// %. if >= 99.99 성공.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Chance;

	bool operator == (const FDebuff& InDebuff) 
	{
		//return ( (Type == InDebuff.Type) && ( Duration == InDebuff.Duration ) && ( Power == InDebuff.Power) && ( ID == InDebuff.ID) );

		return ( ID == InDebuff.ID );
	}
};

USTRUCT(BlueprintType)
struct FEffectorData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DefaultDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DefaultSplashRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDebuff> DebuffArray;
};

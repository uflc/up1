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
	Dead		UMETA(DisplayName = "Dead Animation"),
	Custom1,
	Custom2,
	Custom3	
};				

UENUM(BlueprintType)
enum class ETDSoundType : uint8
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

//타워 업그레이드 타입
UENUM(BlueprintType)
enum class ETalentType : uint8
{
	Weapon,
	ActiveSkill,
	PassiveSkill
};

#define	 UPGRADES_NUM 3//TODO use Enum as Byte as arrry index ?
#define TALENT_LEVEL_MAX 2

UENUM(BlueprintType)
enum class EDebuffType : uint8
{
	Stun,
	Snared,
	Slow,
	Custom
};

class UCustomDebuffBaseComponent;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCustomDebuffBaseComponent> CustomDebuffClass;
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
public:
	//todo :: replace with FDamage
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DefaultDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultSplashRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDebuff> DebuffArray;
};

USTRUCT(BlueprintType)
struct FDamage
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDebuff> DebuffArray;
};

//USTRUCT()
//struct FTDDamageEvent : public FRadialDamageEvent
//{
//	GENERATED_BODY()
//
//	/** ID for this class. NOTE this must be unique for all damage events. */
//	static const int32 ClassID = 3;
//
//	virtual int32 GetTypeID() const override { return FTDDamageEvent::ClassID; };
//	virtual bool IsOfType(int32 InID) const override { return (FTDDamageEvent::ClassID == InID) || FRadialDamageEvent::IsOfType(InID); };
//	
//	FTDDamageEvent()
//	{}
//};
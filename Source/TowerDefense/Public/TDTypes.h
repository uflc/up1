#pragma once

#include "CoreMinimal.h"
#include "TDTypes.generated.h"

//@TODO End �߰� Ÿ��

UENUM(BlueprintType)
enum class EUnitTeam : uint8
{
	None	UMETA(DisplayName = "None"),
	Player	UMETA(DisplayName = "Player"),
	Enemy	UMETA(DisplayName = "Enemy"),
};

//@TDUnit�� �ִϸ��̼� Ÿ��
UENUM(BlueprintType)
enum class EUnitState : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Attacking	UMETA(DisplayName = "Attaking"),
	Running		UMETA(DisplayName = "Running"),
	Dying		UMETA(DisplayName = "Dying"),
	Dead		UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class EWeaponFlipbookType : uint8
{
	Projectile	,
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


//@Ÿ�� � ���������� ���׷��̵� Ÿ��
UENUM(BlueprintType)
enum class ETowerType : uint8
{
	ONE		,
	TWO		,
	THREE		
};

UENUM(BlueprintType)
enum class EDebuffType : uint8
{
	Stun,
	Snared,
	Slow
};

//@TODO ����
UENUM(BlueprintType)
enum class EValueType : uint8
{
	Coin		UMETA(DisplayName = "Coin"),
	Life 		UMETA(DisplayName = "Life"),
	Mana		UMETA(DisplayName = "Mana"),
	//HeroHP		UMETA(DisplayName = "HeroHP")
};

USTRUCT(BlueprintType)
struct  FDebuff
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDebuffType Type;
	
	// Sec
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	// 0~100
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PowerPerStack;

	// Stack with ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentStack;
	//TickInterval

	float GetCalculatedPower() const 
	{
		return Power + PowerPerStack * ( ( CurrentStack < 0 ? 0 : CurrentStack ) - 1);
	}

	//MaxTick
	bool operator == (const FDebuff& InDebuff) 
	{
		//return ( (Type == InDebuff.Type) && ( Duration == InDebuff.Duration ) && ( Power == InDebuff.Power) && ( ID == InDebuff.ID) );

		return ( ID == InDebuff.ID );
	}
};

//@TODO How to use Enum as Byte as arrry index
//@TowerUpDataTree���� Ÿ���� ���� ������ �� �迭�� ����. Ÿ���� Ÿ��(���׷��̵� �ε���)�� ETowerType �� TowerLevel�� �� ���������� ���׷��̵� Ÿ��. 
//typedef  TArray<ETowerType> TowerLevel; //UHT ������

#define	 UPGRADES_NUM 3//�ٸ� ���?
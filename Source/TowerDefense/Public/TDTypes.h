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
struct  FDebuffSet {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDebuffType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Power;
};

//@TODO How to use Enum as Byte as arrry index
//@TowerUpDataTree���� Ÿ���� ���� ������ �� �迭�� ����. Ÿ���� Ÿ��(���׷��̵� �ε���)�� ETowerType �� TowerLevel�� �� ���������� ���׷��̵� Ÿ��. 
//typedef  TArray<ETowerType> TowerLevel; //UHT ������

#define	 UPGRADES_NUM 3//�ٸ� ���?
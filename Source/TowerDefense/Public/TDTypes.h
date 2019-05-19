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

//@TDUnit의 애니메이션 타입
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
enum class EDirection : uint8
{
	LD	UMETA(DisplayName = "Left Dowm"),
	LT  UMETA(DisplayName = "Left Top"),
	RD	UMETA(DisplayName = "Right Down"),
	RT  UMETA(DisplayName = "Right Top"),
};


//@타워 어떤 레벨에서의 업그레이드 타입
UENUM(BlueprintType)
enum class ETowerType : uint8
{
	ONE		,
	TWO		,
	THREE		
};


//@TODO How to use Enum as Byte as arrry index
//@TowerUpDataTree에서 타워의 현재 레벨은 이 배열의 길이. 타워의 타입(업그레이드 인덱스)이 ETowerType 즉 TowerLevel은 각 레벨에서의 업그레이드 타입. 
//typedef  TArray<ETowerType> TowerLevel; //UHT 미지원

#define	 UPGRADES_NUM 3//다른 방법?
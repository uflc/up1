// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperCharacter.h"
#include "MyPaperCharacter.generated.h"

UENUM(BlueprintType)
enum class EUnitState : uint8
{
	Idle		UMETA(DisplayName="Idle"),
	Attacking	UMETA(DisplayName="Attaking"),
	Running		UMETA(DisplayName="Running"),
	Dying		UMETA(DisplayName="Dying"),
	Dead		UMETA(DisplayName="Dead")
};

UENUM(BlueprintType)
enum class EUnitTeam : uint8
{
	None	UMETA(DisplayName = "None"),
	Player	UMETA(DisplayName = "Player"),
	Enemy	UMETA(DisplayName = "Enemy"),
};


/**
 * 
 �� ������ ��� ĳ���� ������ ��ӹ��� Ŭ����.
 ������Ʈ, ��, ���� ��׷� ��� �� ������ ���ֵ鿡�� �������� ��� ����.
 ��ü���� �ൿ ������ BT BP�� ��.
 */
UCLASS(BluePrintable)
class WORK2_API AMyPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

	/*UPROPERTY(Config)
	TArray<FStringAssetReference> UnitFlipbooks;*/

public:
	AMyPaperCharacter();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit State")
	EUnitState UnitState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
	EUnitTeam Team;

	//���ؼ� ���µ�, �����ս� ������ ����ٸ� ���� ���� �ν��Ͻ��� �����ϵ��� �ؾ� �� �� ������ ū ������ ���� ��.
	UPROPERTY(EditAnywhere,	BlueprintReadWrite, Category = "Animation")
	TMap<EUnitState, TAssetPtr<UPaperFlipbook>> FlipbookMap;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
	float AttackRange;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
	float AggroDrawnRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
	float DrawingAggroRange;

	//����
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
	//TSoftObjectPtr<UMyPaperCharacterCommon> Data;


public:
	UFUNCTION(BlueprintCallable, Category = "Animation")
	bool UpdateAnimation();
	//virtual void UpdateAnimation_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Unit State")
	void ChangeState(EUnitState InState);

	void BeginPlay();

	void FlipbooksDeffered();
	
};
